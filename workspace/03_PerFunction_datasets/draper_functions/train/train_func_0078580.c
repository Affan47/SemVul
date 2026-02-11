remove_cmd_completions (list)
     WORD_LIST *list;
{
  WORD_LIST *l;
  int ret;

  for (ret = EXECUTION_SUCCESS, l = list; l; l = l->next)
    {
      if (progcomp_remove (l->word->word) == 0)
	{
	  builtin_error (_("%s: no completion specification"), l->word->word);
	  ret = EXECUTION_FAILURE;
	}
    }
  return ret;
}
