Scan_Choice_Point_Info_3(WamWord b_word, WamWord name_word,
			 WamWord arity_word)
{
  WamWord word, tag_mask;
  WamWord *b;
  int func, arity;

  DEREF(b_word, word, tag_mask);
  b = From_WamWord_To_B(word);

  func = Scan_Choice_Point_Pred(b, &arity);
  if (func < 0)
    return FALSE;

  Get_Atom(func, name_word);
  Get_Integer(arity, arity_word);

  return TRUE;
}
