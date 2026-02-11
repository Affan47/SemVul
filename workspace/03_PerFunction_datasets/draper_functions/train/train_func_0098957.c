CheckDebugInfoIntrinsics(Module *M) {


  if (Function *FuncStart = M->getFunction("llvm.dbg.func.start")) {
    while (!FuncStart->use_empty()) {
      CallInst *CI = cast<CallInst>(FuncStart->use_back());
      CI->eraseFromParent();
    }
    FuncStart->eraseFromParent();
  }

  if (Function *StopPoint = M->getFunction("llvm.dbg.stoppoint")) {
    while (!StopPoint->use_empty()) {
      CallInst *CI = cast<CallInst>(StopPoint->use_back());
      CI->eraseFromParent();
    }
    StopPoint->eraseFromParent();
  }

  if (Function *RegionStart = M->getFunction("llvm.dbg.region.start")) {
    while (!RegionStart->use_empty()) {
      CallInst *CI = cast<CallInst>(RegionStart->use_back());
      CI->eraseFromParent();
    }
    RegionStart->eraseFromParent();
  }

  if (Function *RegionEnd = M->getFunction("llvm.dbg.region.end")) {
    while (!RegionEnd->use_empty()) {
      CallInst *CI = cast<CallInst>(RegionEnd->use_back());
      CI->eraseFromParent();
    }
    RegionEnd->eraseFromParent();
  }

  if (Function *Declare = M->getFunction("llvm.dbg.declare")) {
    if (!Declare->use_empty()) {
      DbgDeclareInst *DDI = cast<DbgDeclareInst>(Declare->use_back());
      if (!isa<MDNode>(DDI->getArgOperand(0)) ||
          !isa<MDNode>(DDI->getArgOperand(1))) {
        while (!Declare->use_empty()) {
          CallInst *CI = cast<CallInst>(Declare->use_back());
          CI->eraseFromParent();
        }
        Declare->eraseFromParent();
      }
    }
  }
}
