findBlock(double* memptr) {
  assert(state==BLOCK);


  U32 h1=0x3D49B113, h2=0x29EB7F93, h3=0x2614BE13, h4=0x3828EB13;

  int c;
  while ((c=dec.get())!=-1) {
    h1=h1*12+c;
    h2=h2*20+c;
    h3=h3*28+c;
    h4=h4*44+c;
    if (h1==0xB16B88F1 && h2==0xFF5376F1 && h3==0x72AC5BF1 && h4==0x2F909AF1)
      break;
  }
  if (c==-1) return false;


  if ((c=dec.get())!=1 && c!=2) error("unsupported ZPAQ level");
  if (dec.get()!=1) error("unsupported ZPAQL type");
  z.read(&dec);
  if (c==1 && z.header.isize()>6 && z.header[6]==0)
    error("ZPAQ level 1 requires at least 1 component");
  if (memptr) *memptr=z.memory();
  state=FILENAME;
  decode_state=FIRSTSEG;
  return true;
}
