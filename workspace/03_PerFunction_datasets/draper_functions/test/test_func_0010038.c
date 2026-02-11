deallocateMemForFunction(const Function *F) {
  ValueMap<const Function *, EmittedCode, EmittedFunctionConfig>::iterator
    Emitted = EmittedFunctions.find(F);
  if (Emitted != EmittedFunctions.end()) {
    MemMgr->deallocateFunctionBody(Emitted->second.FunctionBody);
    MemMgr->deallocateExceptionTable(Emitted->second.ExceptionTable);
    TheJIT->NotifyFreeingMachineCode(Emitted->second.Code);

    EmittedFunctions.erase(Emitted);
  }

  if(JITExceptionHandling) {
    TheJIT->DeregisterTable(F);
  }

  if (JITEmitDebugInfo) {
    DR->UnregisterFunction(F);
  }
}
