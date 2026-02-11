skolem_symbol(int sn)
{
  char *s;
  int dummy;

  s = sn_to_str(sn);
  return(*s == '$' &&
	 (*(s+1) == 'c' || *(s+1) == 'f') &&
	 str_int(s+2,&dummy));
}
