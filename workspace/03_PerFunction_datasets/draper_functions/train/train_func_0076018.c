is_miss_rate_acceptable (unsigned HOST_WIDE_INT cache_line_size,
		   HOST_WIDE_INT step, HOST_WIDE_INT delta,
		   unsigned HOST_WIDE_INT distinct_iters,
		   int align_unit)
{
  unsigned align, iter;
  int total_positions, miss_positions, max_allowed_miss_positions;
  int address1, address2, cache_line1, cache_line2;


  if (delta >= (HOST_WIDE_INT) cache_line_size)
    return false;

  miss_positions = 0;
  total_positions = (cache_line_size / align_unit) * distinct_iters;
  max_allowed_miss_positions = (ACCEPTABLE_MISS_RATE * total_positions) / 1000;


  for (align = 0; align < cache_line_size; align += align_unit)


    for (iter = 0; iter < distinct_iters; iter++)
      {
	address1 = align + step * iter;
	address2 = address1 + delta;
	cache_line1 = address1 / cache_line_size;
	cache_line2 = address2 / cache_line_size;
	if (cache_line1 != cache_line2)
	  {
	    miss_positions += 1;
            if (miss_positions > max_allowed_miss_positions)
	      return false;
          }
      }
  return true;
}
