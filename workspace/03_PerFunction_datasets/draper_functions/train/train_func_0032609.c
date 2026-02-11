attrToString(int64_t attrib) {
  string r="     ";
  if ((attrib&255)=='u') {
    r[0]="0pc3d5b7 9lBsDEF"[(attrib>>20)&15];
    for (int i=0; i<4; ++i)
      r[4-i]=(attrib>>(8+3*i))%8+'0';
  }
  else if ((attrib&255)=='w') {
    for (int i=0, j=0; i<32; ++i) {
      if ((attrib>>(i+8))&1) {
        char c="RHS DAdFTprCoIEivs89012345678901"[i];
        if (j<5) r[j]=c;
        else r+=c;
        ++j;
      }
    }
  }
  return r;
}
