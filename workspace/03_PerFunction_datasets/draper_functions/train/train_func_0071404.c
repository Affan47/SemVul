GetSlice(unsigned int vol, const char *uid)
    {
    assert( vol < UID.size() );
    SliceUIDType::const_iterator cit = UID[vol].begin();
    while (cit != UID[vol].end())
      {
      if (cit->second == uid)
        {
        return static_cast<int>(cit->first);
        }
      ++cit;
      }
    return -1;
    }
