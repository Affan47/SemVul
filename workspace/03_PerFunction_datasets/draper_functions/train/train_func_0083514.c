Size() const
    {
    size_t s = 0;
    std::vector<RoleSelectionSub>::const_iterator it = RSSArray.begin();
    for( ; it != RSSArray.end(); ++it )
      {
      s += it->Size();
      }
    return s;
    }
