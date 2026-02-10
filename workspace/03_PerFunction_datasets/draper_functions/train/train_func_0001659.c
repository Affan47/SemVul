operator==(const CoinIndexedVector & rhs) const
{
  const int cs = rhs.nElements_;

  const int * cind = rhs.indices_;
  const double * celem = rhs.elements_;
  if (nElements_!=cs)
    return false;
  bool okay=true;
  CoinRelFltEq eq(1.0e-8);
  if (!packedMode_&&!rhs.packedMode_) {
    for (int i=0;i<cs;i++) {
      int iRow = cind[i];
      if (!eq(celem[iRow],elements_[iRow])) {
	okay=false;
	break;
      }
    }
  } else if (packedMode_&&rhs.packedMode_) {
    double * temp = new double[CoinMax(capacity_,rhs.capacity_)];
    memset(temp,0,CoinMax(capacity_,rhs.capacity_)*sizeof(double));
    for (int i=0;i<cs;i++) {
      int iRow = cind[i];
      temp[iRow]=celem[i];
    }
    for (int i=0;i<cs;i++) {
      int iRow = cind[i];
      if (!eq(temp[iRow],elements_[i])) {
	okay=false;
	break;
      }
    }
  } else {
    const double * celem2=elements_;
    if (packedMode_) {
      celem2=celem;
      celem=elements_;
    }
    for (int i=0;i<cs;i++) {
      int iRow = cind[i];
      if (!eq(celem2[iRow],celem[i])) {
	okay=false;
	break;
      }
    }
  }
  return okay;
}
