SetFormula(string molFormula)
  {
    string attr = "Formula";
    OBPairData *dp = (OBPairData *) GetData(attr);

    if (dp == NULL)
      {
        dp = new OBPairData;
        dp->SetAttribute(attr);
      }
    dp->SetValue(molFormula);

    dp->SetOrigin(fileformatInput);

    SetData(dp);
  }
