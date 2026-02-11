mayHaveCisTransBond(OBMol *mol)
  {
    std::vector<OBBond*>::iterator ib;
    for (OBBond *bond = mol->BeginBond(ib); bond; bond = mol->NextBond(ib))
      if (bond->GetBO() == 2) {
        return true;
      }
    return false;
  }
