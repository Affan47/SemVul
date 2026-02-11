toArray() const
{
  vector<int> v;
  v.push_back(value);
  return new ArrayMV<int>(driver, v);
}
