runOnModule(Module &M) override {
    for (auto &F : M.functions()) {
      if (F.isDeclaration())
        abort();
    }
    return false;
  }
