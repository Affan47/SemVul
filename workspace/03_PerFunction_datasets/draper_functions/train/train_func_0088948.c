get_string(int i)
{
  if (i<0)
    {

      return nonterminal_table[-i-1];
    }
  else
    {

      return terminal_table[i-1];
    }
}
