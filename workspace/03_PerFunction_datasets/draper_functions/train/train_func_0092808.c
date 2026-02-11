insert(const Type *Ty) {
      if (!Types.insert(Ty))
        return false;
      if (Ty->isAbstract())
        Ty->addAbstractTypeUser(this);
      return true;
    }
