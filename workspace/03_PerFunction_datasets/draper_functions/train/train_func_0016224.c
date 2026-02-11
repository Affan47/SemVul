induceSAs0(unsigned int *SA,
		unsigned char *s, unsigned int *bkt,
		unsigned int n, unsigned int K, bool suffix) {
  unsigned int i, j;


  getBuckets(s, bkt, n, K, true);

  for(i=n-1; i>0; i--)
    if(SA[i]>0) {
      j=SA[i]-1;
      if(getbase(s,j)<=getbase(s,j+1) && bkt[getbase(s,j)]<i) {
        SA[bkt[getbase(s,j)]]=j;
        bkt[getbase(s,j)]--;
        if(!suffix) SA[i]=0;
      }
    }
}
