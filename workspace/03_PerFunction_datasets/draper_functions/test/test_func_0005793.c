Get_Int_From_Word(WamWord start_word)
{
  WamWord word, tag_mask;

  DEREF(start_word, word, tag_mask);

  if (tag_mask != TAG_INT_MASK)
    word = *Get_Int_Addr_From_Gvar(word);

  return UnTag_INT(word);
}
