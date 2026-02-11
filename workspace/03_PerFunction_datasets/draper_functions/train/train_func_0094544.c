vrp_bitmap_equal_p (const_bitmap b1, const_bitmap b2)
{
  return (b1 == b2
	  || ((!b1 || bitmap_empty_p (b1))
	      && (!b2 || bitmap_empty_p (b2)))
	  || (b1 && b2
	      && bitmap_equal_p (b1, b2)));
}
