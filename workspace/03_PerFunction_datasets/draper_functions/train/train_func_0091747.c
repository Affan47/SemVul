GetBrickCount(size_t lod, size_t ts) const
{
  BrickTable::size_type count = 0;
  BrickTable::const_iterator iter = this->bricks.begin();
  for(; iter != this->bricks.end(); ++iter) {
    if(std::get<0>(iter->first) == ts &&
       std::get<1>(iter->first) == lod) {
      ++count;
    }
  }
  return count;
}
