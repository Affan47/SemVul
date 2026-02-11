FCEUI_CheatSearchGetRange(uint32 first, uint32 last, int (*callb)(uint32 a, uint8 last, uint8 current))
{
  uint32 x;
  uint32 in=0;

  if(!CheatComp)
  {
   if(!InitCheatComp())
    CheatMemErr();
   return;
  }

  for(x=0;x<0x10000;x++)
   if(!(CheatComp[x]&CHEATC_NOSHOW) && CheatRPtrs[x>>10])
   {
    if(in>=first)
     if(!callb(x,CheatComp[x],CheatRPtrs[x>>10][x]))
      break;
    in++;
    if(in>last) return;
   }
}
