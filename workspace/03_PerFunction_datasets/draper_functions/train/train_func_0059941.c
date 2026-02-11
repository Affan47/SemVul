mseq (VocoderSetup *vs)
{
   register int x0, x28;

   vs->x >>= 1;

   if (vs->x & B0)
      x0 = 1;
   else
      x0 = -1;

   if (vs->x & B28)
      x28 = 1;
   else
      x28 = -1;

   if (x0 + x28)
      vs->x &= B31_;
   else
      vs->x |= B31;

   return (x0);
}
