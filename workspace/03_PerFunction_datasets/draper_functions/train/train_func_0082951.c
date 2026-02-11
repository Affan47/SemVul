create_noise(uint8 *buf, const int bits, int size)
{
   static int m = 0x0011;
   int xor_val, i;

   for (i = 0; i < size; i++)
   {
      xor_val = m & 1;
      m >>= 1;
      xor_val ^= (m & 1);
      m |= xor_val << (bits - 1);

      buf[i] = m;
   }
}
