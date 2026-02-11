operator<< (const std::list<std::string> &l)
{
  *this << (uint32_t) l.size();
  for (list<string>::const_iterator it = l.begin();
       it != l.end(); ++it )
    *this << *it;
  return *this;
}
