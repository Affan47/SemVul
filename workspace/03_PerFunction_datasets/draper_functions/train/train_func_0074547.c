int_loc_descriptor (HOST_WIDE_INT i)
{
  enum dwarf_location_atom op;


  if (i >= 0)
    {
      int clz = clz_hwi (i);
      int ctz = ctz_hwi (i);
      if (i <= 31)
	op = (enum dwarf_location_atom) (DW_OP_lit0 + i);
      else if (i <= 0xff)
	op = DW_OP_const1u;
      else if (i <= 0xffff)
	op = DW_OP_const2u;
      else if (clz + ctz >= HOST_BITS_PER_WIDE_INT - 5
	       && clz + 5 + 255 >= HOST_BITS_PER_WIDE_INT)


	return int_shift_loc_descriptor (i, HOST_BITS_PER_WIDE_INT - clz - 5);
      else if (clz + ctz >= HOST_BITS_PER_WIDE_INT - 8
	       && clz + 8 + 31 >= HOST_BITS_PER_WIDE_INT)


	return int_shift_loc_descriptor (i, HOST_BITS_PER_WIDE_INT - clz - 8);
      else if (HOST_BITS_PER_WIDE_INT == 32 || i <= 0xffffffff)
	op = DW_OP_const4u;
      else if (clz + ctz >= HOST_BITS_PER_WIDE_INT - 8
	       && clz + 8 + 255 >= HOST_BITS_PER_WIDE_INT)


	return int_shift_loc_descriptor (i, HOST_BITS_PER_WIDE_INT - clz - 8);
      else if (clz + ctz >= HOST_BITS_PER_WIDE_INT - 16
	       && clz + 16 + (size_of_uleb128 (i) > 5 ? 255 : 31)
		  >= HOST_BITS_PER_WIDE_INT)


	return int_shift_loc_descriptor (i, HOST_BITS_PER_WIDE_INT - clz - 16);
      else if (clz + ctz >= HOST_BITS_PER_WIDE_INT - 32
	       && clz + 32 + 31 >= HOST_BITS_PER_WIDE_INT
	       && size_of_uleb128 (i) > 6)

	return int_shift_loc_descriptor (i, HOST_BITS_PER_WIDE_INT - clz - 32);
      else
	op = DW_OP_constu;
    }
  else
    {
      if (i >= -0x80)
	op = DW_OP_const1s;
      else if (i >= -0x8000)
	op = DW_OP_const2s;
      else if (HOST_BITS_PER_WIDE_INT == 32 || i >= -0x80000000)
	{
	  if (size_of_int_loc_descriptor (i) < 5)
	    {
	      dw_loc_descr_ref ret = int_loc_descriptor (-i);
	      add_loc_descr (&ret, new_loc_descr (DW_OP_neg, 0, 0));
	      return ret;
	    }
	  op = DW_OP_const4s;
	}
      else
	{
	  if (size_of_int_loc_descriptor (i)
	      < (unsigned long) 1 + size_of_sleb128 (i))
	    {
	      dw_loc_descr_ref ret = int_loc_descriptor (-i);
	      add_loc_descr (&ret, new_loc_descr (DW_OP_neg, 0, 0));
	      return ret;
	    }
	  op = DW_OP_consts;
	}
    }

  return new_loc_descr (op, i, 0);
}
