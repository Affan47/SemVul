fire( const HepVector& mu, const HepSymMatrix& S ) {

  HepMatrix U;
  HepVector sigmas;

  if (mu.num_row() == S.num_row()) {
    prepareUsigmas ( S, U, sigmas );
    return mu + deviates ( U, sigmas, localEngine, set, nextGaussian );
  } else {
    std::cerr << "In firing RandMultiGauss distribution with explicit mu and S: \n"
         << "      Dimension of mu (" << mu.num_row() <<
	    ") does not match dimension of S (" << S.num_row() << ")\n";
    std::cerr << "---Exiting to System\n";
    exit(1);
  }
  return mu;


}
