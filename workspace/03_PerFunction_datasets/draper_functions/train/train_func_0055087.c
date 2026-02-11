GetCParam(OBAtom* atom)
  {
    if (atom->GetAtomicNum() == 5)
      return 0.704;
    if (atom->IsCarbon())
      return 1.016;
    if (atom->IsNitrogen())
      return 1.113;
    if (atom->IsOxygen())
      return 1.337;
    if (atom->GetAtomicNum() == 14)
      return 0.811;
    if (atom->IsPhosphorus())
      return 1.068;
    if (atom->IsSulfur())
      return 1.249;
    if (atom->GetAtomicNum() == 17)
      return 1.078;
    if (atom->GetAtomicNum() == 33)
      return 0.825;

    return 0.0;
  }
