Cop_toK_Aop_24( GenefxState *gfxs )
{
     int   w   = gfxs->length;
     u8   *D   = gfxs->Aop[0];
     u8    Dkr = (gfxs->Dkey & 0xff0000) >> 16;
     u8    Dkg = (gfxs->Dkey & 0x00ff00) >>  8;
     u8    Dkb = (gfxs->Dkey & 0x0000ff);

     while (w--) {
          if (D[0] == Dkb && D[1] == Dkg && D[2] == Dkr) {
               D[0] = gfxs->color.b;
               D[1] = gfxs->color.g;
               D[2] = gfxs->color.r;
          }

          D += 3;
     }
}
