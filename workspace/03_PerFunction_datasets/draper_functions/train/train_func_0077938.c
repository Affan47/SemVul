sum() const
{
  ftype s = 0.0;
  for ( int i = 0; i < data.size(); i++ ) s += data[i];
  return s;
}
