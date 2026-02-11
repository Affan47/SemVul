decompress(int n) {
  assert(state==DATA);
  assert(decode_state!=SKIP);


  if (decode_state==FIRSTSEG) {
    dec.init();
    assert(z.header.size()>5);
    pp.init(z.header[4], z.header[5]);
    decode_state=SEG;
  }


  while ((pp.getState()&3)!=1)
    pp.write(dec.decompress());


  while (n) {
    int c=dec.decompress();
    pp.write(c);
    if (c==-1) {
      state=SEGEND;
      return false;
    }
    if (n>0) --n;
  }
  return true;
}
