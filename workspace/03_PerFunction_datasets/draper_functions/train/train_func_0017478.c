excluded_rtx (int idx)
{
  return ((strcmp (defs[idx].enumname, "CONST_DOUBLE") == 0)
	  || (strcmp (defs[idx].enumname, "CONST_FIXED") == 0));
}
