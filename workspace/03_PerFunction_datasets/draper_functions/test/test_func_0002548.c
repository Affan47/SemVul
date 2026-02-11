endDelimLocation() const
{
  Location loc(items_.back().loc);
  loc += chars_.size() - items_.back().index;
  return loc;
}
