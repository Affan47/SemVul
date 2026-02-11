Gen_Sym(char *prefix, int gen_sym_hash)
{
  unsigned pl = strlen(prefix);
  unsigned hp = Hash_String(prefix);
  unsigned x, i;
  unsigned radix_p;
  char *str;

  strcpy(gen_sym_buff, prefix);
  str = gen_sym_buff + pl;

  x = (gen_sym_hash - hp) % MAX_ATOM;

  radix_p = 1;
  for (i = 0; i < pl; i++)
    radix_p *= INV_RADIX_MOD_MAX_ATOM;
  radix_p %= MAX_ATOM;


  x *= radix_p;
  x %= MAX_ATOM;

  do
    {
      *str++ = hash_inv_tbl[x % RADIX];
      x /= RADIX;
    }
  while (x);

  *str = '\0';


#ifdef DEBUG
  if (Hash_String(gen_sym_buff) != gen_sym_hash)
    {
      DBGPRINTF("Gensym prefix: (%s) wanted hash: %d\n", prefix,
		gen_sym_hash);
      DBGPRINTF("   new string: (%s)    new hash: %d\n", gen_sym_buff,
		Hash_String(gen_sym_buff));
    }

#endif

  return gen_sym_buff;
}
