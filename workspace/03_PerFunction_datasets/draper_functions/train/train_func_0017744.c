find(const std::string &property, const bool lookInParent) const
{
  boost::any value;

  for (Stack_t::const_iterator it = m_stack.begin(); value.empty() && (m_stack.end() != it); ++it)
  {
    if (*it)
      value = (*it)->getPropertyMap().get(property, lookInParent);
  }

  return value;
}
