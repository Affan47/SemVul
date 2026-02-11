elementAddress(size_t g, size_t e)
{
  if (g >= elements_.size())
    elements_.resize(g + 1);
  Vector<Addressable *> &v = elements_[g];
  for (size_t i = v.size(); i <= e; i++)
    v.push_back((Addressable *)0);
  if (!v[e])
    v[e] = new Addressable(g, e);
  return v[e];
}
