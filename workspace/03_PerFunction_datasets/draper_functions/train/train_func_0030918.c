vect_strided_store_supported (tree vectype, unsigned HOST_WIDE_INT count)
{
  enum machine_mode mode = TYPE_MODE (vectype);


  if (exact_log2 (count) == -1)
    {
      if (vect_print_dump_info (REPORT_DETAILS))
	fprintf (vect_dump, "the size of the group of strided accesses"
		 " is not a power of 2");
      return false;
    }


  if (VECTOR_MODE_P (mode))
    {
      unsigned int i, nelt = GET_MODE_NUNITS (mode);
      unsigned char *sel = XALLOCAVEC (unsigned char, nelt);
      for (i = 0; i < nelt / 2; i++)
	{
	  sel[i * 2] = i;
	  sel[i * 2 + 1] = i + nelt;
	}
      if (can_vec_perm_p (mode, false, sel))
	{
	  for (i = 0; i < nelt; i++)
	    sel[i] += nelt / 2;
	  if (can_vec_perm_p (mode, false, sel))
	    return true;
	}
    }

  if (vect_print_dump_info (REPORT_DETAILS))
    fprintf (vect_dump, "interleave op not supported by target.");
  return false;
}
