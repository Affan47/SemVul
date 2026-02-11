Rd_Chars_Str(WamWord start_word, char *str)
{
  WamWord word, tag_mask;
  WamWord save_start_word;
  WamWord *lst_adr;
  int n = 0;

  save_start_word = start_word;

  for (;;)
    {
      DEREF(start_word, word, tag_mask);

      if (word == NIL_WORD)
	break;

      lst_adr = UnTag_LST(word);

      *str++ = Rd_Char_Check(Car(lst_adr));
      n++;

      start_word = Cdr(lst_adr);
    }

  *str = '\0';
  return n;
}
