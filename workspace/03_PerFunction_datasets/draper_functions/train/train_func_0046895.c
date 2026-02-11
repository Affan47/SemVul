Foreign_Rd_IO_Arg(int arg_long, WamWord start_word, long (*rd_fct) (),
		  int fio_arg_index)
{
  WamWord word, tag_mask;
  FIOArg *fa = fio_arg_array + fio_arg_index;

  DEREF(start_word, word, tag_mask);

  fa->is_var = fa->unify = (tag_mask == TAG_REF_MASK);

  if (rd_fct == NULL)
    fa->value.l = (long) word;
  else if (!fa->is_var)
    {
      if (arg_long)
	{
	  fa->value.l = (*rd_fct) (word);
	  if (arg_long == 2)
	    fa->value.s = Strdup(fa->value.s);
	}
      else
	fa->value.d = (*(double (*)()) rd_fct) (word);
    }

  return fa;
}
