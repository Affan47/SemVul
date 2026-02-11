isExtended256BitVector() const {
  return isExtendedVector() && getSizeInBits() == 256;
}
