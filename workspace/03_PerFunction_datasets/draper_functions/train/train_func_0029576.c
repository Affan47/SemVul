del(int i, int n) {
  int j;

  if (i >= 0 && n > 0 && i + n > 0) {
    if (i + n > length) {
      n = length - i;
    }
    for (j = i; j <= length - n; ++j) {
      s[j] = s[j + n];
    }
    resize(length - n);
  }
  return this;
}
