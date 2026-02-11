Dacc_premultiply( GenefxState *gfxs )
{
     int                w = gfxs->length;
     GenefxAccumulator *D = gfxs->Dacc;

     while (w--) {
          if (!(D->RGB.a & 0xF000)) {
               register u16 Da = D->RGB.a + 1;

               D->RGB.r = (Da * D->RGB.r) >> 8;
               D->RGB.g = (Da * D->RGB.g) >> 8;
               D->RGB.b = (Da * D->RGB.b) >> 8;
          }

          D++;
     }
}
