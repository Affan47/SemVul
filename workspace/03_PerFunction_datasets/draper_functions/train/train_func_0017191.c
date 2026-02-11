Unify_Local_Value(WamWord start_word)
{
  WamWord word, tag_mask;
  WamWord *adr;

  if (S != WRITE_MODE)
    return Unify(start_word, *S++);

  DEREF(start_word, word, tag_mask);

  if (tag_mask == TAG_REF_MASK && Is_A_Local_Adr(adr = UnTag_REF(word)))
    Globalize_Local_Unbound_Var(adr, word);
  else
    {
      Do_Copy_Of_Word(tag_mask, word);
      Global_Push(word);
    }

  return TRUE;
}
