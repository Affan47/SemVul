AddStackProtect(Function *F)
    {
	BasicBlock &BB = F->getEntryBlock();
	if (isa<AllocaInst>(BB.begin())) {


#if LLVM_VERSION < 29


	    F->addFnAttr(Attribute::StackProtectReq);
#endif
	}


#if LLVM_VERSION < 29
	F->addFnAttr(Attribute::StackProtect);
#endif
    }
