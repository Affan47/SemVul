e8e9(unsigned char* buf, int n) {
  for (int i=n-5; i>=0; --i) {
    if (((buf[i]&254)==0xe8) && ((buf[i+4]+1)&254)==0) {
      unsigned a=(buf[i+1]|buf[i+2]<<8|buf[i+3]<<16)+i;
      buf[i+1]=a;
      buf[i+2]=a>>8;
      buf[i+3]=a>>16;
    }
  }
}
