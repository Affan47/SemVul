runOnModule(Module &M) {

      if (!deleteStuff)
        M.setModuleInlineAsm("");


      for (Module::global_iterator I = M.global_begin(), E = M.global_end();
           I != E; ++I) {
        if (deleteStuff == (bool)Named.count(I) && !I->isDeclaration()) {
          I->setInitializer(0);
	} else {
	  if (I->hasAvailableExternallyLinkage())
	    continue;
	  if (I->getName() == "llvm.global_ctors")
	    continue;
	}

        if (I->hasLocalLinkage())
          I->setVisibility(GlobalValue::HiddenVisibility);
        I->setLinkage(GlobalValue::ExternalLinkage);
      }


      for (Module::iterator I = M.begin(), E = M.end(); I != E; ++I) {
        if (deleteStuff == (bool)Named.count(I) && !I->isDeclaration()) {
          I->deleteBody();
	} else {
	  if (I->hasAvailableExternallyLinkage())
	    continue;
	}

        if (I->hasLocalLinkage())
          I->setVisibility(GlobalValue::HiddenVisibility);
        I->setLinkage(GlobalValue::ExternalLinkage);
      }

      return true;
    }
