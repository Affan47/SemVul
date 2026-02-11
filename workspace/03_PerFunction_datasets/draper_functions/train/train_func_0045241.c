isDigit(int x, int radix) {
  return (x >= '0' && x <= '9' && x < '0' + radix)
      || (radix > 10 && x >= 'a' && x < 'a' + radix - 10)
      || (radix > 10 && x >= 'A' && x < 'A' + radix - 10);
}
