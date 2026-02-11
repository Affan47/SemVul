airShuffle_r(airRandMTState *state,
             unsigned int *buff, unsigned int N, int perm) {
  unsigned int i;


  if (!(buff && N > 0)) {
    return;
  }

  for (i=0; i<N; i++) {
    buff[i] = i;
  }
  if (perm) {
    unsigned int swp, tmp;
    while (N > 1) {
      swp = airRandInt_r(state, N);
      N--;
      tmp = buff[N];
      buff[N] = buff[swp];
      buff[swp] = tmp;
    }
  }

}
