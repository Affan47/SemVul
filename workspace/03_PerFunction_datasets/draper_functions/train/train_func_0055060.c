tinf_inflate_uncompressed_block(TINF_DATA *d)
{
   unsigned int length, invlength;
   unsigned int i;

   if((d->sourceLen + 4) > d->sourceSize) return TINF_DATA_ERROR;

   length = d->source[1];
   length = (length << 8) + d->source[0];


   invlength = d->source[3];
   invlength = (invlength << 8) + d->source[2];


   if (length != (~invlength & 0x0000ffff)) return TINF_DATA_ERROR;

   d->source += 4;
   d->sourceLen += 4;


   if ((d->sourceLen + length) > d->sourceSize) return TINF_DATA_ERROR;
   if ((*d->destLen + length) > d->destSize) return TINF_DATA_ERROR;
   for (i = length; i; --i) *d->dest++ = *d->source++;


   d->bitcount = 0;

   d->sourceLen += length;
   *d->destLen += length;

   return TINF_OK;
}
