Rd_Code_Check(WamWord start_word)
{
  int c;

  c = Rd_Integer_Check(start_word);
  if (!Is_Valid_Code(c))
    Pl_Err_Representation(representation_character_code);

  return c;
}
