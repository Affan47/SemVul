CheckSpriteHit(int p)
{
 int l=p-16;
 int x;

 if(sphitx==0x100) return;
 for(x=sphitx;x<(sphitx+8) && x<l;x++)
   if((sphitdata&(0x80>>(x-sphitx))) && !(Plinef[x]&64))
   {
    PPU_status|=0x40;

    sphitx=0x100;
    break;
   }
}
