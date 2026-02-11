get_nonterminal(string * s)
{
  int result;
  vector<string>::iterator it;
  it=find(nonterminal_table.begin(), nonterminal_table.end(), *s);
  if (it==nonterminal_table.end())
    {

      nonterminal_table.push_back(*s);
      result=nonterminal_table.size()-1;
    }
  else
    result=it-nonterminal_table.begin();

  return -result-1;
}
