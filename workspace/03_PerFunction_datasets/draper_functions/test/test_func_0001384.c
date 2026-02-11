alternative_allows_const_pool_ref (rtx mem ATTRIBUTE_UNUSED,
				   const char *constraint, int altnum)
{
  int c;


  while (altnum > 0)
    {
      while (*constraint++ != ',')
	;
      altnum--;
    }


  for (; (c = *constraint) && c != ',' && c != '#';
       constraint += CONSTRAINT_LEN (c, constraint))
    {
      if (c == TARGET_MEM_CONSTRAINT || c == 'o')
	return true;
#ifdef EXTRA_CONSTRAINT_STR
      if (EXTRA_MEMORY_CONSTRAINT (c, constraint)
	  && (mem == NULL || EXTRA_CONSTRAINT_STR (mem, c, constraint)))
	return true;
#endif
    }
  return false;
}
