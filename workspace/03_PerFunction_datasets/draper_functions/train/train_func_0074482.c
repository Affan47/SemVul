ReadARK(int w)
{
 uint8 ret=0;

 if(NESArk[w].readbit>=8)
  ret|=1<<4;
 else
 {
  ret|=((NESArk[w].mzx>>(7-NESArk[w].readbit))&1)<<4;
  if(!fceuindbg)
   NESArk[w].readbit++;
 }
 ret|=(NESArk[w].mzb&1)<<3;
 return(ret);
}
