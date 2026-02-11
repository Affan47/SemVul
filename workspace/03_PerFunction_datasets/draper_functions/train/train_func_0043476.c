Xacc_blend_invsrcalpha( GenefxState *gfxs )
{
     int                w = gfxs->length;
     GenefxAccumulator *X = gfxs->Xacc;

     if (gfxs->Sacc) {
          GenefxAccumulator *S = gfxs->Sacc;

          while (w--) {
               if (!(X->RGB.a & 0xF000)) {
                    register u16 Sa = 0x100 - S->RGB.a;

                    X->RGB.r = (Sa * X->RGB.r) >> 8;
                    X->RGB.g = (Sa * X->RGB.g) >> 8;
                    X->RGB.b = (Sa * X->RGB.b) >> 8;
                    X->RGB.a = (Sa * X->RGB.a) >> 8;
               }

               X++;
               S++;
          }
     }
     else {
          register u16 Sa = 0x100 - gfxs->color.a;

          while (w--) {
               if (!(X->RGB.a & 0xF000)) {
                    X->RGB.a = (Sa * X->RGB.a) >> 8;
                    X->RGB.r = (Sa * X->RGB.r) >> 8;
                    X->RGB.g = (Sa * X->RGB.g) >> 8;
                    X->RGB.b = (Sa * X->RGB.b) >> 8;
               }

               X++;
          }
     }
}
