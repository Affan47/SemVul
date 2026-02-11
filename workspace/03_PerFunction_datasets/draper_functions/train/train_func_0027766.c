merge_charset_and_collation(CHARSET_INFO *cs, CHARSET_INFO *cl)
{
  if (cl)
  {
    if (!my_charset_same(cs, cl))
    {
      my_error(ER_COLLATION_CHARSET_MISMATCH, MYF(0), cl->name, cs->csname);
      return NULL;
    }
    return cl;
  }
  return cs;
}
