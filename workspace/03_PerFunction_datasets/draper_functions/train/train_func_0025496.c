speex_bits_unpack_unsigned(SpeexBits *bits, int nbBits)
{
   unsigned int d=0;
   if ((bits->charPtr<<LOG2_BITS_PER_CHAR)+bits->bitPtr+nbBits>bits->nbBits)
      bits->overflow=1;
   if (bits->overflow)
      return 0;
   while(nbBits)
   {
      d<<=1;
      d |= (bits->chars[bits->charPtr]>>(BITS_PER_CHAR-1 - bits->bitPtr))&1;
      bits->bitPtr++;
      if (bits->bitPtr==BITS_PER_CHAR)
      {
         bits->bitPtr=0;
         bits->charPtr++;
      }
      nbBits--;
   }
   return d;
}
