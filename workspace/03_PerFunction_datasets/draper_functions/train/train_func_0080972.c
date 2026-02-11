flat() {
  unsigned int y;

   if( count624 >= N ) {
    register int i;

    for( i=0; i < NminusM; ++i ) {
      y = (mt[i] & 0x80000000) | (mt[i+1] & 0x7fffffff);
      mt[i] = mt[i+M]       ^ (y >> 1) ^ ((y & 0x1) ? 0x9908b0df : 0x0 );
    }

    for(    ; i < N-1    ; ++i ) {
      y = (mt[i] & 0x80000000) | (mt[i+1] & 0x7fffffff);
      mt[i] = mt[i-NminusM] ^ (y >> 1) ^ ((y & 0x1) ? 0x9908b0df : 0x0 );
    }

    y = (mt[i] & 0x80000000) | (mt[0] & 0x7fffffff);
    mt[i] = mt[M-1] ^ (y >> 1) ^ ((y & 0x1) ? 0x9908b0df : 0x0 );

    count624 = 0;
  }

  y = mt[count624];
  y ^= ( y >> 11);
  y ^= ((y << 7 ) & 0x9d2c5680);
  y ^= ((y << 15) & 0xefc60000);
  y ^= ( y >> 18);

  return                      y * twoToMinus_32()  +
         (mt[count624++] >> 11) * twoToMinus_53()  +
                	    nearlyTwoToMinus_54();
}
