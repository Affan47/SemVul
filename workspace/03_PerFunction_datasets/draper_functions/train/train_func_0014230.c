unget_bits (int num)
{
  if (!littlenums_left)
    {
      ++littlenum_pointer;
      ++littlenums_left;
      bits_left_in_littlenum = num;
    }
  else if (bits_left_in_littlenum + num > LITTLENUM_NUMBER_OF_BITS)
    {
      bits_left_in_littlenum =
	num - (LITTLENUM_NUMBER_OF_BITS - bits_left_in_littlenum);
      ++littlenum_pointer;
      ++littlenums_left;
    }
  else
    bits_left_in_littlenum += num;
}
