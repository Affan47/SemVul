Rd_Number_Check(WamWord start_word)
{
  WamWord word, tag_mask;

  DEREF(start_word, word, tag_mask);
  if (tag_mask == TAG_REF_MASK)
    Pl_Err_Instantiation();

  if (tag_mask != TAG_FLT_MASK && tag_mask != TAG_INT_MASK)
    Pl_Err_Type(type_number, word);

  if (tag_mask == TAG_INT_MASK)
    return (double) UnTag_INT(word);

  return Obtain_Float(UnTag_FLT(word));
}
