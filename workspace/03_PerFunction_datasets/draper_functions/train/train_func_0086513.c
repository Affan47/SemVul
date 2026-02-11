shouldExplore(const Use *U) override {
      Instruction *I = cast<Instruction>(U->getUser());

      if (BeforeHere == I && !IncludeI)
        return false;

      if (isSafeToPrune(I))
        return false;

      return true;
    }
