Bop_rgb24_to_Aop_rgb16_LE( GenefxState *gfxs )
{
     int  w = gfxs->length;
     u8  *S = gfxs->Bop[0];
     u16 *D = gfxs->Aop[0];

     while ((unsigned long)S & 3) {
          *D++ = PIXEL_RGB16( S[0], S[1], S[2] );

          S += 3;
          w -= 1;
     }

     if ((unsigned long)D & 2) {
          *D++ = PIXEL_RGB16( S[0], S[1], S[2] );

          w -= 1;
          S += 3;

          while (w > 1) {
               *(u32*)D = PIXEL_RGB16( S[0], S[1], S[2] ) | (PIXEL_RGB16( S[3], S[4], S[5] ) << 16);

               w -= 2;
               D += 2;
               S += 6;
          }
     }
     else {
          u32 *S32 = (u32*)S;
          u32 *D32 = (u32*)D;

          while (w > 3) {
               D32[0] = BGR_TO_RGB16(  S32[0] ) | (BGR_TO_RGB16( (S32[0] >> 24) | (S32[1] <<  8) ) << 16);
               D32[1] = BGR_TO_RGB16( (S32[1] >> 16) | (S32[2] << 16) ) | (BGR_TO_RGB16( S32[2] >> 8 ) << 16);

               D32 += 2;
               S32 += 3;
               w   -= 4;
          }

          S = (u8*)  S32;
          D = (u16*) D32;
     }

     while (w > 0) {
          *D++ = PIXEL_RGB16( S[0], S[1], S[2] );

          w -= 1;
          S += 3;
     }
}
