getState (const std::vector<unsigned long> & v) {
  if (v.size() != VECTOR_STATE_SIZE ) {
    std::cerr <<
    	"\nRandEngine get:state vector has wrong length - state unchanged\n";
    return false;
  }
  theSeed   = v[1];
  int count = v[2];
  setSeed(theSeed,0);
  while (seq < count) flat();
  return true;
}
}
