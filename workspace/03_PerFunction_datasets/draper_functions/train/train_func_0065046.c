GetSSSR()
  {
    if (!HasSSSRPerceived())
      FindSSSR();

    OBRingData *rd = 0;
    if (!HasData("SSSR")) {
      rd = new OBRingData();
      rd->SetAttribute("SSSR");
      SetData(rd);
    }

    rd = (OBRingData *) GetData("SSSR");
    rd->SetOrigin(perceived);
    return(rd->GetData());
  }
