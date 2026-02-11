domlcmp(_cdomain dom1, _cdomain dom2) {
  _domain a = (_domain) dom1;
  _domain b = (_domain) dom2;
  if (*a != *b) return false;
  for (int t = 1; t <= *a; t++)
    if (tolower(a[t]) != tolower(b[t])) return false;
  return true;
}
