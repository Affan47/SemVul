captured(const Use *U) override {
      if (isa<ReturnInst>(U->getUser()) && !ReturnCaptures)
        return false;

      if (!shouldExplore(U))
        return false;

      Captured = true;
      return true;
    }
