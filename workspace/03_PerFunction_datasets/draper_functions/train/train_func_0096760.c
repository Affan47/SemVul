getBuckets(unsigned char *s,
  unsigned int *bkt, unsigned int n,
  unsigned int K, bool end) {
  unsigned int i, sum=0;


  for(i=0; i<K; i++) bkt[i]=0;


  for(i=0; i<n; i++) bkt[s[i]]++;

  for(i=0; i<K; i++) {
    sum+=bkt[i];
    bkt[i]=end ? sum-1 : sum-bkt[i];
  }
}
