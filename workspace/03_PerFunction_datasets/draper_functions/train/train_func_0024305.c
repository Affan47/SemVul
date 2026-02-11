Rd_Float(WamWord start_word)
{
  WamWord word, tag_mask;

  DEREF(start_word, word, tag_mask);

  return Obtain_Float(UnTag_FLT(word));
}
