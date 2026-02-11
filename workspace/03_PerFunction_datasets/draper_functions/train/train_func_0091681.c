lex_identifier (pfile, cur)
     cpp_reader *pfile;
     const uchar *cur;
{
  size_t len;
  uchar *out = pfile->out.cur;
  cpp_hashnode *result;

  do
    {
      do
	*out++ = *cur++;
      while (is_numchar (*cur));
      cur = skip_escaped_newlines (pfile, cur);
    }
  while (is_numchar (*cur));

  CUR (pfile->context) = cur;
  len = out - pfile->out.cur;
  result = (cpp_hashnode *) ht_lookup (pfile->hash_table, pfile->out.cur,
				       len, HT_ALLOC);
  pfile->out.cur = out;
  return result;
}
