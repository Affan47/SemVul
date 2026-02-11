Bop_a1_set_alphapixel_Aop_a8( GenefxState *gfxs )
{
     int   i;
     int   w = gfxs->length;
     u8   *S = gfxs->Bop[0];
     u8   *D = gfxs->Aop[0];

     for (i=0; i<w; i++) {
          if (S[i>>3] & (0x80 >> (i&7)))
               D[i] = 0xff;
     }
}
