MMC5Synco(void)
{
 int x;

 MMC5PRG();
 for(x=0;x<4;x++)
 {
  switch((NTAMirroring>>(x<<1))&3)
   {
    case 0:PPUNTARAM|=1<<x;vnapage[x]=NTARAM;break;
    case 1:PPUNTARAM|=1<<x;vnapage[x]=NTARAM+0x400;break;
    case 2:PPUNTARAM|=1<<x;vnapage[x]=ExRAM;break;
    case 3:PPUNTARAM&=~(1<<x);vnapage[x]=MMC5fill;break;
   }
 }
 MMC5WRAM(0x6000,WRAMPage&7);
 if(!ABMode)
 {
  MMC5CHRB();
  MMC5CHRA();
 }
 else
 {
   MMC5CHRA();
   MMC5CHRB();
 }
  {
    uint32 t;
    t=NTFill|(NTFill<<8)|(NTFill<<16)|(NTFill<<24);
    FCEU_dwmemset(MMC5fill,t,0x3c0);
  }
  {
   unsigned char moop;
   uint32 t;
   moop=ATFill|(ATFill<<2)|(ATFill<<4)|(ATFill<<6);
   t=moop|(moop<<8)|(moop<<16)|(moop<<24);
   FCEU_dwmemset(MMC5fill+0x3c0,t,0x40);
  }
  X6502_IRQEnd(FCEU_IQEXT);
  MMC5HackCHRMode=CHRMode&3;
}
