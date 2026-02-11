Sop_lut8_to_Dacc( GenefxState *gfxs )
{
     int                w = gfxs->length;
     GenefxAccumulator *D = gfxs->Dacc;
     u8                *S = gfxs->Sop[0];

     DFBColor *entries = gfxs->Slut->entries;

     while (w--) {
          u8 s = *S++;

          D->RGB.a = entries[s].a;
          D->RGB.r = entries[s].r;
          D->RGB.g = entries[s].g;
          D->RGB.b = entries[s].b;

          D++;
     }
}
