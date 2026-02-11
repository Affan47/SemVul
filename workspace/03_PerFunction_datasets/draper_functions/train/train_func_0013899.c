panner_align() {

  Catalog* catalog = unidraw->GetCatalog();

  Alignment alignment = BottomRight;
  if (const char* panner_align = catalog->GetAttribute("panner_align")) {
    const int nalign = 15;
    const char *alignmentstr[nalign] = {
      "tl", "tc", "tr", "cl", "c", "cr", "cl", "bl", "br",
      "l", "r", "t", "b", "hc", "vc"
    };
    if (isdigit(*panner_align))
      alignment = atoi(panner_align);
    else {
      int n=0;
      while (n<nalign) {
	if (strcmp(alignmentstr[n], panner_align)==0) {
	  alignment = n;
	  break;
	}
	n++;
      }
    }
  }
  return alignment;
}
