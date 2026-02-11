printer_zxp_read(libspectrum_word port GCC_UNUSED,
				         int *attached)
{
if(!settings_current.printer)
  return(0xff);
if(!printer_graphics_enabled)
  return(0xff);
if(plusd_available)
  return(0xff);

*attached=1;

if(!zxpspeed)
  return 0x3e;
else
  {
  int frame=frames-zxpframes;
  int cycles=tstates-zxpcycles;
  int pix=zxppixel;
  int sp=zxpnewspeed;
  int x,ans;
  int cpp=440/zxpspeed;

  if(frame>400)
    frame=400;
  cycles+=frame*machine_current->timings.tstates_per_frame;
  x=cycles/cpp-64;

  while(x>320)
    {
    pix=-1;
    x-=384;
    if(sp)
      {
      x=(x+64)*cpp;
      cpp=440/sp;
      x=x/cpp-64;
      sp=0;
      }
    }
  if((x>-10 && x<0) | zxpstylus)
    ans=0xbe;
  else
    ans=0x3e;
  if(x>pix)
    ans|=1;
  return ans;
  }
}
