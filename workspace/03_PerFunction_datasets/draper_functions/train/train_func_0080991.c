Cop_to_Aop_24( GenefxState *gfxs )
{
     int   w = gfxs->length;
     u8   *D = gfxs->Aop[0];

     while (w) {
          D[0] = gfxs->color.b;
          D[1] = gfxs->color.g;
          D[2] = gfxs->color.r;

          D += 3;
          --w;
     }
}
