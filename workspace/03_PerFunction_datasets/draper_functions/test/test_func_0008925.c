lapic_startap(uchar apicid, uint addr)
{
  int i;
  ushort *wrv;


  outb(IO_RTC, 0xF);
  outb(IO_RTC+1, 0x0A);
  wrv = (ushort*)(0x40<<4 | 0x67);
  wrv[0] = 0;
  wrv[1] = addr >> 4;


  lapicw(ICRHI, apicid<<24);
  lapicw(ICRLO, INIT | LEVEL | ASSERT);
  microdelay(200);
  lapicw(ICRLO, INIT | LEVEL);
  microdelay(100);


  for(i = 0; i < 2; i++){
    lapicw(ICRHI, apicid<<24);
    lapicw(ICRLO, STARTUP | (addr>>12));
    microdelay(200);
  }
}
