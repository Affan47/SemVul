initByArray(unsigned int lenkey, unsigned int key[])
{
  int i, j, k;

  initBySeed(19650218UL);

  i=1; j=0;
  k = (N>lenkey ? N : lenkey);
  for (; k; k--)
  {
    U[i] = (U[i] ^ ((U[i-1] ^ (U[i-1] >> 30)) * 1664525UL))
      + key[j] + j;
    U[i] &= 0xffffffffUL;
    i++; j++;
    if (i>=N) { U[0] = U[N-1]; i=1; }
    if (j>=(int)lenkey) j=0;
  }
  for (k=N-1; k; k--)
  {
    U[i] = (U[i] ^ ((U[i-1] ^ (U[i-1] >> 30)) * 1566083941UL))
      - i;
    U[i] &= 0xffffffffUL;
    i++;
    if (i>=N) { U[0] = U[N-1]; i=1; }
  }

  U[0] = 0x80000000UL;

}
