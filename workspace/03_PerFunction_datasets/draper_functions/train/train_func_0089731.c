get_rule(int nt)
{
  Rule * result=0;

  list<Rule *>::iterator ri;
  for (ri=rules.begin(); ri!=rules.end(); ri++)
    if ((*ri)->get_left()==nt)
      result=(*ri);


  return result;
}
