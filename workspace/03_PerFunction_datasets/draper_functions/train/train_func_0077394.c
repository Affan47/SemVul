xtensa_return_in_msb (const_tree valtype)
{
  return (TARGET_BIG_ENDIAN
	  && AGGREGATE_TYPE_P (valtype)
	  && int_size_in_bytes (valtype) >= UNITS_PER_WORD);
}
