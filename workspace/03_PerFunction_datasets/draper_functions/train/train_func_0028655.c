TrimStrRight( const std::wstring& Src, const std::wstring& c)
  {
    size_t p2 = Src.find_last_not_of(c);
    if (p2 == std::wstring::npos) {return std::wstring();}
    size_t p1 = Src.find_first_not_of(c);
    if (p1 == std::wstring::npos) p1 = 0;
    return Src.substr(0, p2+1);
  }
