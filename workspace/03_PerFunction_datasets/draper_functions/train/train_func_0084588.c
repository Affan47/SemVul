M90PPU(uint32 A)
{
  if((IRQMode&3)==2)
  {
    if(lastread!=A)
    {
      ClockCounter();
      ClockCounter();
    }
    lastread=A;
  }

  if(is209)
  {
    uint8 l,h;
    h=A>>8;
    if(h<0x20&&((h&0x0F)==0xF))
    {
      l=A&0xF0;
      if(l==0xD0)
      {
        chr[(h&0x10)>>4]=((h&0x10)>>2);
        tekvrom();
      }
      else if(l==0xE0)
      {
        chr[(h&0x10)>>4]=((h&0x10)>>2)|2;
        tekvrom();
      }
    }
  }
  else
  {
    chr[0]=0;
    chr[1]=4;
  }
}
