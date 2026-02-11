Dacc_set_alpha( GenefxState *gfxs )
{
     int                w = gfxs->length;
     GenefxAccumulator *D = gfxs->Dacc;
     int                a = gfxs->color.a;

     while (w--) {
          if (!(D->RGB.a & 0xF000)) {
               D->RGB.a = a;
          }

          D++;
     }
}
