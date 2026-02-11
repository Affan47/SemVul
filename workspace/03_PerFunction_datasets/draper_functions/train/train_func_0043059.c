size_of_int_loc_descriptor (HOST_WIDE_INT i)
{
  unsigned long s;

  if (i >= 0)
    {
      int clz, ctz;
      if (i <= 31)
	return 1;
      else if (i <= 0xff)
	return 2;
      else if (i <= 0xffff)
	return 3;
      clz = clz_hwi (i);
      ctz = ctz_hwi (i);
      if (clz + ctz >= HOST_BITS_PER_WIDE_INT - 5
	  && clz + 5 + 255 >= HOST_BITS_PER_WIDE_INT)
	return size_of_int_shift_loc_descriptor (i, HOST_BITS_PER_WIDE_INT
						    - clz - 5);
      else if (clz + ctz >= HOST_BITS_PER_WIDE_INT - 8
	       && clz + 8 + 31 >= HOST_BITS_PER_WIDE_INT)
	return size_of_int_shift_loc_descriptor (i, HOST_BITS_PER_WIDE_INT
						    - clz - 8);
      else if (HOST_BITS_PER_WIDE_INT == 32 || i <= 0xffffffff)
	return 5;
      s = size_of_uleb128 ((unsigned HOST_WIDE_INT) i);
      if (clz + ctz >= HOST_BITS_PER_WIDE_INT - 8
	  && clz + 8 + 255 >= HOST_BITS_PER_WIDE_INT)
	return size_of_int_shift_loc_descriptor (i, HOST_BITS_PER_WIDE_INT
						    - clz - 8);
      else if (clz + ctz >= HOST_BITS_PER_WIDE_INT - 16
	       && clz + 16 + (s > 5 ? 255 : 31) >= HOST_BITS_PER_WIDE_INT)
	return size_of_int_shift_loc_descriptor (i, HOST_BITS_PER_WIDE_INT
						    - clz - 16);
      else if (clz + ctz >= HOST_BITS_PER_WIDE_INT - 32
	       && clz + 32 + 31 >= HOST_BITS_PER_WIDE_INT
	       && s > 6)
	return size_of_int_shift_loc_descriptor (i, HOST_BITS_PER_WIDE_INT
						    - clz - 32);
      else
	return 1 + s;
    }
  else
    {
      if (i >= -0x80)
	return 2;
      else if (i >= -0x8000)
	return 3;
      else if (HOST_BITS_PER_WIDE_INT == 32 || i >= -0x80000000)
	{
	  if (-(unsigned HOST_WIDE_INT) i != (unsigned HOST_WIDE_INT) i)
	    {
	      s = size_of_int_loc_descriptor (-i) + 1;
	      if (s < 5)
		return s;
	    }
	  return 5;
	}
      else
	{
	  unsigned long r = 1 + size_of_sleb128 (i);
	  if (-(unsigned HOST_WIDE_INT) i != (unsigned HOST_WIDE_INT) i)
	    {
	      s = size_of_int_loc_descriptor (-i) + 1;
	      if (s < r)
		return s;
	    }
	  return r;
	}
    }
}
