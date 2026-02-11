get ( std::istream & is ) {
  std::string inName;
  is >> inName;
  if (inName != name()) {
    is.clear(std::ios::badbit | is.rdstate());
    std::cerr << "Mismatch when expecting to read state of a "
    	      << name() << " distribution\n"
	      << "Name found was " << inName
	      << "\nistream is left in the badbit state\n";
    return is;
  }
  std::string c1;
  std::string c2;
  if (possibleKeywordInput(is, "Uvec", c1)) {
    std::vector<unsigned long> t(2);
    is >> defaultMean >> t[0] >> t[1]; defaultMean = DoubConv::longs2double(t);
    is >> defaultStdDev>>t[0]>>t[1]; defaultStdDev = DoubConv::longs2double(t);
    std::string ng;
    is >> ng;
    set = false;
	#ifdef TRACE_IO
	if (ng != "nextGauss")
	std::cout << "get(): ng = " << ng << "\n";
	#endif
    if (ng == "nextGauss") {
      is >> nextGauss >> t[0] >> t[1]; nextGauss = DoubConv::longs2double(t);
	#ifdef TRACE_IO
	std::cout << "get(): nextGauss read back as " << nextGauss << "\n";
	#endif
      set = true;
    }
    return is;
  }

  is >> defaultMean >> c2 >> defaultStdDev;
  if ( (!is) || (c1 != "Mean:") || (c2 != "Sigma:") ) {
    std::cerr << "i/o problem while expecting to read state of a "
    	      << name() << " distribution\n"
	      << "default mean and/or sigma could not be read\n";
    return is;
  }
  is >> c1 >> c2 >> nextGauss;
  if ( (!is) || (c1 != "RANDGAUSS") ) {
    is.clear(std::ios::badbit | is.rdstate());
    std::cerr << "Failure when reading caching state of RandGauss\n";
    return is;
  }
  if (c2 == "CACHED_GAUSSIAN:") {
    set = true;
  } else if (c2 == "NO_CACHED_GAUSSIAN:") {
    set = false;
  } else {
    is.clear(std::ios::badbit | is.rdstate());
    std::cerr << "Unexpected caching state keyword of RandGauss:" << c2
	      << "\nistream is left in the badbit state\n";
  }
  return is;
}
