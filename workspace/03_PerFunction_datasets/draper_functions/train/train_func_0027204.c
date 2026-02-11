induceSAs0(unsigned int *SA,
  unsigned char *s, unsigned int *bkt,
  unsigned int n, unsigned int K, bool suffix) {
  unsigned int i, j;


  getBuckets(s, bkt, n, K, true);

  for(i=n-1; i>0; i--)
    if(SA[i]>0) {
      j=SA[i]-1;
      if(s[j]<=s[j+1] && bkt[s[j]]<i) {
        SA[bkt[s[j]]]=j;
        bkt[s[j]]--;
        if(!suffix) SA[i]=0;
      }
    }
}
