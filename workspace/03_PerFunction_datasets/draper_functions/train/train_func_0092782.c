maxEndoLag() const
{
  int val = 0;
  for (vector<expr_t>::const_iterator it = arguments.begin();
       it != arguments.end(); it++)
    val = max(val, (*it)->maxEndoLag());
  return val;
}
