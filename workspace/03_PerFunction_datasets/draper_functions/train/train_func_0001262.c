speex_bits_peek_unsigned(SpeexBits *bits, int nbBits)
{
   unsigned int d=0;
   int bitPtr, charPtr;
   char *chars;

   if ((bits->charPtr<<LOG2_BITS_PER_CHAR)+bits->bitPtr+nbBits>bits->nbBits)
     bits->overflow=1;
   if (bits->overflow)
      return 0;

   bitPtr=bits->bitPtr;
   charPtr=bits->charPtr;
   chars = bits->chars;
   while(nbBits)
   {
      d<<=1;
      d |= (chars[charPtr]>>(BITS_PER_CHAR-1 - bitPtr))&1;
      bitPtr++;
      if (bitPtr==BITS_PER_CHAR)
      {
         bitPtr=0;
         charPtr++;
      }
      nbBits--;
   }
   return d;
}
