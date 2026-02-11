GARandomSeed(unsigned int s) {
  if(s == 0 && seed == 0) {
    unsigned long int tmp;
    while(seed == 0) {
      tmp = time(NULL) _GA_PID;
      for(unsigned int i=0; i<GALIB_BITS_IN_WORD*sizeof(unsigned int); i++)
	seed += (tmp & (1 << i));
    }
    _GA_RND_SEED (seed);
    bitseed(seed);
  }
  else if(s != 0 && seed != s) {
    seed = s;
    _GA_RND_SEED (seed);
    bitseed(seed);
  }
}
