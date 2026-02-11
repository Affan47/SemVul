induceSAl0(unsigned int *SA,
		unsigned char *s, unsigned int *bkt,
		unsigned int n, unsigned int K, bool suffix) {
  unsigned int i, j;


  getBuckets(s, bkt, n, K, false);

  bkt[0]++;
  for(i=0; i<n; i++)
    if(SA[i]>0) {
      j=SA[i]-1;
      if(getbase(s,j)>=getbase(s,j+1)) {
        SA[bkt[getbase(s,j)]]=j;
        bkt[getbase(s,j)]++;
        if(!suffix && i>0) SA[i]=0;
      }
    }
}
