BandInterp(int nbands, int band) {
    switch (nbands) {
      case 1: return GCI_GrayIndex;
      case 2: return ((band==1)?GCI_GrayIndex:GCI_AlphaBand);
      case 3:
      case 4:
        if (band<3)
            return ((band==1)?GCI_RedBand:GCI_GreenBand);
        return ((band==3)?GCI_BlueBand:GCI_AlphaBand);
      default:
        return GCI_Undefined;
    }
}
