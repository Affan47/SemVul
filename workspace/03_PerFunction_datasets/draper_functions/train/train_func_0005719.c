GetZParam(OBAtom* atom)
  {
    if (atom->IsHydrogen())
      return 1.395;
    if (atom->IsCarbon())
      return 2.494;
    if (atom->IsNitrogen())
      return 2.711;
    if (atom->IsOxygen())
      return 3.045;
    if (atom->GetAtomicNum() == 9)
      return 2.847;
    if (atom->GetAtomicNum() == 14)
      return 2.350;
    if (atom->IsPhosphorus())
      return 2.350;
    if (atom->IsSulfur())
      return 2.980;
    if (atom->GetAtomicNum() == 17)
      return 2.909;
    if (atom->GetAtomicNum() == 35)
      return 3.017;
    if (atom->GetAtomicNum() == 53)
      return 3.086;

    return 0.0;
  }
