Sop_lut8_SKto_Dacc( GenefxState *gfxs )
{
     int w     = gfxs->length;
     int i     = gfxs->Xphase;
     int SperD = gfxs->SperD;

     GenefxAccumulator *D    = gfxs->Dacc;
     u8                *S    = gfxs->Sop[0];
     u32                Skey = gfxs->Skey;

     DFBColor *entries = gfxs->Slut->entries;

     while (w--) {
          u8 s = S[i>>16];

          if (s != Skey) {
               D->RGB.a = entries[s].a;
               D->RGB.r = entries[s].r;
               D->RGB.g = entries[s].g;
               D->RGB.b = entries[s].b;
          }
          else
               D->RGB.a = 0xF000;

          i += SperD;

          D++;
     }
}
