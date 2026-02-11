smix(char* b, int r, int n) {
  libzpaq::Array<U32> x(32*r), v(32*r*n);
  for (int i=0; i<r*128; ++i) x[i/4]+=(b[i]&255)<<i%4*8;
  for (int i=0; i<n; ++i) {
    memcpy(&v[i*r*32], &x[0], r*128);
    blockmix(&x[0], r);
  }
  for (int i=0; i<n; ++i) {
    U32 j=x[(2*r-1)*16]&(n-1);
    for (int k=0; k<r*32; ++k) x[k]^=v[j*r*32+k];
    blockmix(&x[0], r);
  }
  for (int i=0; i<r*128; ++i) b[i]=x[i/4]>>(i%4*8);
}
