allInsertY() const
{
  vector<TState> res;
  for (TTerm t = 0; t < terminals; ++t)
    res.push_back (TransInsertY (t));
  return res;
}
