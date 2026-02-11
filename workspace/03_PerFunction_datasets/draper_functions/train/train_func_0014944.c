Cacc_to_Dacc( GenefxState *gfxs )
{
     int                w    = gfxs->length;
     GenefxAccumulator *D    = gfxs->Dacc;
     GenefxAccumulator  Cacc = gfxs->Cacc;

     while (w--)
          *D++ = Cacc;
}
