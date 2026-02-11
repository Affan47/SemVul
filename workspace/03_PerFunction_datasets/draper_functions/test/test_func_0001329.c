AddChain(void) {
    VOMSTrustChain chain;
    return *chains_.insert(chains_.end(),chain);
  }
