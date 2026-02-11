FixMMC3PRG(int V)
{
          if(V&0x40)
          {
           pwrap(0xC000,DRegBuf[6]);
           pwrap(0x8000,~1);
          }
          else
          {
           pwrap(0x8000,DRegBuf[6]);
           pwrap(0xC000,~1);
          }
	  pwrap(0xA000,DRegBuf[7]);
	  pwrap(0xE000,~0);
}
