eq(const char* str, size_t len) const {
  const char* aData = _data;
  const char* bData = str;

  size_t aLength = _length;
  size_t bLength = len;

  if (bLength == kInvalidIndex) {
    size_t i;
    for (i = 0; i < aLength; i++) {
      if (aData[i] != bData[i] || bData[i] == 0)
        return false;
    }

    return bData[i] == 0;
  }
  else {
    if (aLength != bLength)
      return false;

    return ::memcmp(aData, bData, aLength) == 0;
  }
}
