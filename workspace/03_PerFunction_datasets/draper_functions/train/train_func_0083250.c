EmitBranchToAt(uint64_t At, uint64_t To, bool isCall, bool is64Bit){
  intptr_t Offset = ((intptr_t)To - (intptr_t)At) >> 2;
  unsigned *AtI = (unsigned*)(intptr_t)At;

  if (Offset >= -(1 << 23) && Offset < (1 << 23)) {
    AtI[0] = BUILD_B(Offset, isCall);
  } else if (!is64Bit) {
    AtI[0] = BUILD_LIS(12, To >> 16);
    AtI[1] = BUILD_ORI(12, 12, To);
    AtI[2] = BUILD_MTCTR(12);
    AtI[3] = BUILD_BCTR(isCall);
  } else {
    AtI[0] = BUILD_LIS(12, To >> 48);
    AtI[1] = BUILD_ORI(12, 12, To >> 32);
    AtI[2] = BUILD_SLDI(12, 12, 32);
    AtI[3] = BUILD_ORIS(12, 12, To >> 16);
    AtI[4] = BUILD_ORI(12, 12, To);
    AtI[5] = BUILD_MTCTR(12);
    AtI[6] = BUILD_BCTR(isCall);
  }
}
