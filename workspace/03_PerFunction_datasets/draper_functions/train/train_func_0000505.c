getContextName(const DIScope *Context, std::string &N) {
    if (auto *NS = dyn_cast<DINamespace>(Context)) {
      if (!NS->getName().empty()) {
        getContextName(NS->getScope(), N);
        N = N + NS->getName().str() + "::";
      }
    } else if (auto *TY = dyn_cast<DIType>(Context)) {
      if (!TY->getName().empty()) {
        getContextName(TY->getScope().resolve(TypeIdentifierMap), N);
        N = N + TY->getName().str() + "::";
      }
    }
  }
