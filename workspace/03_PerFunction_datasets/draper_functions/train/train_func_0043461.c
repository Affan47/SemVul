color_shift(unsigned int mask)
{
   unsigned char i = 0;

   if(!mask) return(0);
   while(!((mask >> i) & 1)) ++i;
   return(i);
}
