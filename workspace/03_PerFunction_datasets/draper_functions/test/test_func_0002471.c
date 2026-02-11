Sop_rgb332_to_Dacc( GenefxState *gfxs )
{
     int                w = gfxs->length;
     GenefxAccumulator *D = gfxs->Dacc;
     u8                *S = gfxs->Sop[0];

     while (w--) {
          u8 s = *S++;

          D->RGB.a = 0xFF;
          D->RGB.r = EXPAND_3to8(s >> 5);
          D->RGB.g = EXPAND_3to8((s & 0x1C) >> 2);
          D->RGB.b = EXPAND_2to8(s & 0x03);

          D++;
     }
}
