Put_Unsafe_Value(WamWord start_word)
{
  WamWord word, tag_mask;
  WamWord *adr;
  WamWord res_word;

  DEREF(start_word, word, tag_mask);

  if (tag_mask == TAG_REF_MASK &&
      (adr = UnTag_REF(word)) >= (WamWord *) EE(E))
    {
      Globalize_Local_Unbound_Var(adr, res_word);
      return res_word;
    }

  Do_Copy_Of_Word(tag_mask, word);
  return word;
}
