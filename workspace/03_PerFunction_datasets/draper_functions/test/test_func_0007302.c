definedInCaller(Value *V) const {
      if (isa<Argument>(V)) return true;
      if (Instruction *I = dyn_cast<Instruction>(V))
        if (!BlocksToExtract.count(I->getParent()))
          return true;
      return false;
    }
