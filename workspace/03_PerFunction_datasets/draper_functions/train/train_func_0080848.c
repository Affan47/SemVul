getIndexOfOut(int iSys, int iPos) const {
  for (int iMem = 0; iMem < sizeOut(iSys); ++iMem)
    if (systems[iSys].iOut[iMem] == iPos) return iMem;


  return -1;
}
