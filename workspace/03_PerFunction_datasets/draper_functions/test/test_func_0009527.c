RAMBO1_hb(void)
{
      if(IRQmode) return;
      if(scanline==240) return;

      rmode=0;
      IRQCount--;
      if(IRQCount==0xFF)
      {
       if(IRQa)
       {
        rmode = 1;
        X6502_IRQBegin(FCEU_IQEXT);
       }
      }
}
