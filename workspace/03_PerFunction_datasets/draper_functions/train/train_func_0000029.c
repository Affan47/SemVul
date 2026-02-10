operator[](const set<int> &t)
{
  if(has_not(t))
  {
    index[t] = index.size()-1;
    element.push_back(&(index.find(t)->first));
  }
  return index[t];
}
