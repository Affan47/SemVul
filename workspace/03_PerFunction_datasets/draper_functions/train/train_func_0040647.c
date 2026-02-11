runOnFunction(Function &F) {
  if (!EnableARCOpts)
    return false;


  if (!Run)
    return false;

  bool Changed = false;

  for (inst_iterator I = inst_begin(&F), E = inst_end(&F); I != E; ++I) {
    Instruction *Inst = &*I;

    switch (GetBasicInstructionClass(Inst)) {
    case IC_Retain:
    case IC_RetainRV:
    case IC_Autorelease:
    case IC_AutoreleaseRV:
    case IC_FusedRetainAutorelease:
    case IC_FusedRetainAutoreleaseRV:


      Changed = true;
      Inst->replaceAllUsesWith(cast<CallInst>(Inst)->getArgOperand(0));
      break;
    default:
      break;
    }
  }

  return Changed;
}
