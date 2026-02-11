restoreStatus( const char filename[] ) {
  std::ifstream inFile(filename, std::ios::in);
  if (!checkFile ( inFile, filename, engineName(), "restoreStatus" )) {
    std::cerr << "  -- Engine state remains unchanged\n";
    return;
  }
  if ( possibleKeywordInput ( inFile, "Uvec", theSeed ) ) {
    std::vector<unsigned long> v;
    unsigned long xin;
    for (unsigned int ivec=0; ivec < VECTOR_STATE_SIZE; ++ivec) {
      inFile >> xin;
	       #ifdef TRACE_IO
	       std::cout << "ivec = " << ivec << "  xin = " << xin << "    ";
	       if (ivec%3 == 0) std::cout << "\n";
	       #endif
      if (!inFile) {
        inFile.clear(std::ios::badbit | inFile.rdstate());
        std::cerr << "\nHurd160Engine state (vector) description improper."
	       << "\nrestoreStatus has failed."
	       << "\nInput stream is probably mispositioned now." << std::endl;
        return;
      }
      v.push_back(xin);
    }
    getState(v);
    return;
  }

  if( !inFile.bad() ) {

    inFile >> wordIndex;
    for( int i = 0; i < 5; ++i ) {
        inFile >> words[i];
    }
  }
}
