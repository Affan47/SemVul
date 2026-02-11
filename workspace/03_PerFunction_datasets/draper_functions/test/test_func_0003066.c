getRadixFmt() {
  switch (Radix) {
  case octal:
    return PRIo64;
  case decimal:
    return PRIu64;
  case hexadecimal:
    return PRIx64;
  }
  return nullptr;
}
