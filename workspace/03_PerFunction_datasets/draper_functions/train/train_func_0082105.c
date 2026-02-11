SetFramesIndex(int lb, int ub)
  {
    if ((lb == this->mp_FramesIndex[0]) && (ub == this->mp_FramesIndex[1]))
      return;
    this->mp_FramesIndex[0] = lb;
    this->mp_FramesIndex[1] = ub;
    this->Modified();
  }
