Un_Boolean(int value, WamWord start_word)
{
  return Get_Atom(value ? atom_true : atom_false, start_word);
}
