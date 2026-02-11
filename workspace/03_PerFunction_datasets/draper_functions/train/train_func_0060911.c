isSegmentSelected(FXint s) const {
  if(s<0 || s>=nsegs){ fxerror("FXGradientBar::isSegmentSelected: argument out of range."); }
  return sellower<=s && s<=selupper;
  }
