list_remove_pattern (list, pattern, patspec, itype, quoted)
     WORD_LIST *list;
     char *pattern;
     int patspec, itype, quoted;
{
  WORD_LIST *new, *l;
  WORD_DESC *w;
  char *tword;

  for (new = (WORD_LIST *)NULL, l = list; l; l = l->next)
    {
      tword = remove_pattern (l->word->word, pattern, patspec);
      w = alloc_word_desc ();
      w->word = tword ? tword : savestring ("");
      new = make_word_list (w, new);
    }

  l = REVERSE_LIST (new, WORD_LIST *);
  tword = string_list_pos_params (itype, l, quoted);
  dispose_words (l);

  return (tword);
}
