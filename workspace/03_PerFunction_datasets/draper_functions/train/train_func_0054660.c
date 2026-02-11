_make_words(long *l, long n) {
  long i, j;
  long marker[33];
  long *r=_ogg_malloc(n*sizeof(long));
  memset(marker, 0, sizeof(marker));

  for (i=0; i<n; i++) {
    long length=l[i];
    if (length>0) {
      long entry=marker[length];

      if (length<32 && (entry>>length)) {
        _ogg_free(r);
        return NULL;
      }
      r[i]=entry;

      {
        for (j=length; j>0; j--) {

          if (marker[j]&1) {
            if (j==1)
              marker[1]++;
            else
              marker[j]=marker[j-1]<<1;
            break;
          }
          marker[j]++;
        }
      }

      for (j=length+1; j<33; j++)
        if ((marker[j]>>1) == entry) {
          entry=marker[j];
          marker[j]=marker[j-1]<<1;
        }else
          break;
    }
  }

  for (i=0; i<n; i++) {
    long temp=0;
    for (j=0; j<l[i]; j++) {
      temp<<=1;
      temp|=r[i]>>j&1;
    }
    r[i]=temp;
  }

  return r;
}
