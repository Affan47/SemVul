passEnumerate(const PassInfo *P) {
      if (P->isCFGOnlyPass())
        CFGOnlyList.push_back(P->getTypeInfo());
    }
