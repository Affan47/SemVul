create(TargetMachine *TM) {
  std::unique_ptr<TargetMachine> TheTM(TM);


  if (sys::DynamicLibrary::LoadLibraryPermanently(nullptr, ErrorStr))
    return nullptr;


  if (MemMgr) {
    if (WhichEngine & EngineKind::JIT)
      WhichEngine = EngineKind::JIT;
    else {
      if (ErrorStr)
        *ErrorStr = "Cannot create an interpreter with a memory manager.";
      return nullptr;
    }
  }


  if ((WhichEngine & EngineKind::JIT) && TheTM) {
    Triple TT(M->getTargetTriple());
    if (!TM->getTarget().hasJIT()) {
      errs() << "WARNING: This target JIT is not designed for the host"
             << " you are running.  If bad things happen, please choose"
             << " a different -march switch.\n";
    }

    ExecutionEngine *EE = nullptr;
    if (ExecutionEngine::OrcMCJITReplacementCtor && UseOrcMCJITReplacement) {
      EE = ExecutionEngine::OrcMCJITReplacementCtor(ErrorStr, std::move(MemMgr),
                                                    std::move(Resolver),
                                                    std::move(TheTM));
      EE->addModule(std::move(M));
    } else if (ExecutionEngine::MCJITCtor)
      EE = ExecutionEngine::MCJITCtor(std::move(M), ErrorStr, std::move(MemMgr),
                                      std::move(Resolver), std::move(TheTM));

    if (EE) {
      EE->setVerifyModules(VerifyModules);
      return EE;
    }
  }


  if (WhichEngine & EngineKind::Interpreter) {
    if (ExecutionEngine::InterpCtor)
      return ExecutionEngine::InterpCtor(std::move(M), ErrorStr);
    if (ErrorStr)
      *ErrorStr = "Interpreter has not been linked in.";
    return nullptr;
  }

  if ((WhichEngine & EngineKind::JIT) && !ExecutionEngine::MCJITCtor) {
    if (ErrorStr)
      *ErrorStr = "JIT has not been linked in.";
  }

  return nullptr;
}
