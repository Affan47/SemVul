hasAnyImmediateCodes() const {
    for (unsigned i = 0, e = Operands.size(); i != e; ++i)
      if (Operands[i].isImm() && Operands[i].getImmCode() != 0)
        return true;
    return false;
  }
