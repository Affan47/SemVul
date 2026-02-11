DrawZapper(int w, uint8 *buf, int arg)
{
 if(arg)
  FCEU_DrawGunSight(buf, ZD[w].mzx,ZD[w].mzy);
}
