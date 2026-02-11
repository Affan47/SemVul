Mapper19_StateRestore(int version)
{
 int x;

 SyncPRG();
 FixNTAR();
 FixCRR();
 for(x=0x40;x<0x80;x++)
  FixCache(x,IRAM[x]);
}
