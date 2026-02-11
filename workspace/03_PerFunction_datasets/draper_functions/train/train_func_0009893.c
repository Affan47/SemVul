ftsym_findbyval(struct ftsym *ftsym, u_int32 val, char **name)
{
  struct ftchash_rec_sym *ftch_recsymp;
  u_int32 hash;

  if (!ftsym)
    return 0;

  hash = ((val>>16) ^ (val & 0xFFFF)) & 0x0FFF;

  if (!(ftch_recsymp = ftchash_lookup(ftsym->ftch, &val, hash)))
    return 0;

  *name = ftch_recsymp->str;
  return 1;

}
