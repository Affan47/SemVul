parseSegmentOrSectionName(const char *P) {
  if (P[15] == 0)

    return P;

  return StringRef(P, 16);
}
