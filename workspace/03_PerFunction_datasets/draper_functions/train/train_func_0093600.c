GetEnergy(int ci)
  {
    if (!HasData(OBGenericDataType::ConformerData))
      SetData(new OBConformerData);
    OBConformerData *cd = (OBConformerData*) GetData(OBGenericDataType::ConformerData);
    vector<double> energies = cd->GetEnergies();

    if (((unsigned int)ci >= energies.size()) || (ci < 0))
      return 0.0;

    return energies[ci];
  }
