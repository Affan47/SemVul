hp_scale_to_8bit(int count, register unsigned char *data, int depth,
                 hp_bool_t invert)
{
    register unsigned int tmp, mask;
    register hp_bool_t lowbyte_first = is_lowbyte_first_byteorder ();
    unsigned int shift1 = depth-8;
    int k;
    unsigned char *dataout = data;

    if ((count <= 0) || (shift1 <= 0)) return;

    mask = 1;
    for (k = 1; k < depth; k++) mask |= (1 << k);

    if (lowbyte_first)
    {
      while (count--) {
         tmp = ((((unsigned int)data[0])<<8) | ((unsigned int)data[1])) & mask;
         tmp >>= shift1;
         if (invert) tmp = ~tmp;
         *(dataout++) = tmp & 255U;
         data += 2;
      }
    }
    else
    {
      while (count--) {
         tmp = ((((unsigned int)data[0])<<8) | ((unsigned int)data[1])) & mask;
         tmp >>= shift1;
         if (invert) tmp = ~tmp;
         *(dataout++) = tmp & 255U;
         data += 2;
      }
    }
}
