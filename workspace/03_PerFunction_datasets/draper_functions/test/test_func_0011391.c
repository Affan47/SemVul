get( std::istream & is ) {
  char beginMarker [MarkerLen];
  char endMarker   [MarkerLen];

  is >> std::ws;
  is.width(MarkerLen);
  is >> beginMarker;
  if (strcmp(beginMarker,"Tausworthe-begin")) {
    is.clear(std::ios::badbit | is.rdstate());
    std::cerr << "\nInput mispositioned or"
              << "\nTausworthe state description missing or"
              << "\nwrong engine type found." << std::endl;
  }
  for (int i = 0; i < 4; ++i) {
    is >> words[i];
  }
  is >> wordIndex;
  is >> std::ws;
  is.width(MarkerLen);
  is >> endMarker;
  if (strcmp(endMarker,"Tausworthe-end")) {
    is.clear(std::ios::badbit | is.rdstate());
    std::cerr << "\nTausworthe state description incomplete."
              << "\nInput stream is probably mispositioned now." << std::endl;
  }
}
