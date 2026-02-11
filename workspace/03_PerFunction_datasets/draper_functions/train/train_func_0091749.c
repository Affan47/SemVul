gbksortorder(uint16 i)
{
  uint idx=gbktail(i);
  if (idx>0x7f) idx-=0x41;
  else idx-=0x40;
  idx+=(gbkhead(i)-0x81)*0xbe;
  return 0x8100+gbk_order[idx];
}
