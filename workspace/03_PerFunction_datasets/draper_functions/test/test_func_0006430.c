formatOpenElements(const Vector<OpenElementInfo> &openElementInfo,
					  OutputCharStream &os)
{
  unsigned nOpenElements = openElementInfo.size();
  for (unsigned i = 0;; i++) {
    if (i > 0
      && (i == nOpenElements || openElementInfo[i].included)) {

      const OpenElementInfo &prevInfo = openElementInfo[i - 1];
      if (prevInfo.matchType.size() != 0) {
	os << " (" << prevInfo.matchType;
	if (prevInfo.matchIndex != 0)
	  os << '[' << (unsigned long)prevInfo.matchIndex << ']';
	os << ')';
      }
    }
    if (i == nOpenElements)
      break;
    const OpenElementInfo &e = openElementInfo[i];
    os << ' ' << e.gi;
    if (i > 0 && !e.included) {
      unsigned long n = openElementInfo[i - 1].matchIndex;
      if (n != 0)
	os << '[' << n << ']';
    }
  }
}
