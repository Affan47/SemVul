Fd_Domain_Bool_1(WamWord list_word)
{
  WamWord word, tag_mask;
  WamWord save_list_word;
  WamWord *lst_adr;


  DEREF(list_word, word, tag_mask);
  if (tag_mask == TAG_REF_MASK || tag_mask == TAG_INT_MASK ||
      tag_mask == TAG_FDV_MASK)
    return Fd_Check_For_Bool_Var(word);

  save_list_word = list_word;
  for (;;)
    {
      DEREF(list_word, word, tag_mask);

      if (tag_mask == TAG_REF_MASK)
	Pl_Err_Instantiation();

      if (word == NIL_WORD)
	break;

      if (tag_mask != TAG_LST_MASK)
	Pl_Err_Type(type_list, save_list_word);

      lst_adr = UnTag_LST(word);
      if (!Fd_Check_For_Bool_Var(Car(lst_adr)))
	return FALSE;

      list_word = Cdr(lst_adr);
    }

  return TRUE;
}
