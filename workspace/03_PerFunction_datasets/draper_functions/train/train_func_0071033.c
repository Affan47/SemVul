getState ( std::istream & is ) {
  if ( possibleKeywordInput ( is, "Uvec", theSeed ) ) {
    std::vector<unsigned long> v;
    unsigned long uu;
    for (unsigned int ivec=0; ivec < VECTOR_STATE_SIZE; ++ivec) {
      is >> uu;
      if (!is) {
        is.clear(std::ios::badbit | is.rdstate());
        std::cerr << "\nDualRand state (vector) description improper."
		<< "\ngetState() has failed."
	       << "\nInput stream is probably mispositioned now." << std::endl;
        return is;
      }
      v.push_back(uu);
    }
    getState(v);
    return (is);
  }


  char endMarker   [MarkerLen];
  tausworthe.get(is);
  integerCong.get(is);
  is >> std::ws;
  is.width(MarkerLen);
   is >> endMarker;
  if (strcmp(endMarker,"DualRand-end")) {
    is.clear(std::ios::badbit | is.rdstate());
    std::cerr << "DualRand state description incomplete."
	      << "\nInput stream is probably mispositioned now." << std::endl;
    return is;
  }
  return is;
}
