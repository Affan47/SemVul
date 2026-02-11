c_build_bitfield_integer_type (unsigned HOST_WIDE_INT width, int unsignedp)
{


  if (width == TYPE_PRECISION (integer_type_node))
    return unsignedp ? unsigned_type_node : integer_type_node;
  if (width == TYPE_PRECISION (signed_char_type_node))
    return unsignedp ? unsigned_char_type_node : signed_char_type_node;
  if (width == TYPE_PRECISION (short_integer_type_node))
    return unsignedp ? short_unsigned_type_node : short_integer_type_node;
  if (width == TYPE_PRECISION (long_integer_type_node))
    return unsignedp ? long_unsigned_type_node : long_integer_type_node;
  if (width == TYPE_PRECISION (long_long_integer_type_node))
    return (unsignedp ? long_long_unsigned_type_node
	    : long_long_integer_type_node);
  if (int128_integer_type_node
      && width == TYPE_PRECISION (int128_integer_type_node))
    return (unsignedp ? int128_unsigned_type_node
	    : int128_integer_type_node);
  return build_nonstandard_integer_type (width, unsignedp);
}
