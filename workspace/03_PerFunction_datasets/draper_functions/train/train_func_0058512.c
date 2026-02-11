align(APInt Size, uint64_t Align) {
  if (RoundToAlign && Align)
    return APInt(IntTyBits, RoundUpToAlignment(Size.getZExtValue(), Align));
  return Size;
}
