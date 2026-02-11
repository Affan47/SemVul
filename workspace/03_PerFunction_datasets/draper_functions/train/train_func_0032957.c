contains(key_t val) const
{
  data_t::const_iterator it=std::upper_bound(data.begin(),data.end(),std::make_pair(val,npos));
  if (it==data.begin()) {
    return false;
  }
  --it;
  return (val<it->second);
}
