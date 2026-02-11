Rd_Byte_Check(WamWord start_word)
{
  WamWord word, tag_mask;
  int c;

  DEREF(start_word, word, tag_mask);
  if (tag_mask == TAG_REF_MASK)
    Pl_Err_Instantiation();

  c = UnTag_INT(word);
  if (tag_mask != TAG_INT_MASK || !Is_Valid_Byte(c))
    Pl_Err_Type(type_byte, word);

  return c;
}
