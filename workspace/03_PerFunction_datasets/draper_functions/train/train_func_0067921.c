setResonancePtr(
  ResonanceWidths* resonancePtrIn) {
  if (resonancePtr == resonancePtrIn) return;
  if (resonancePtr != 0) delete resonancePtr;
  resonancePtr = resonancePtrIn;
}
