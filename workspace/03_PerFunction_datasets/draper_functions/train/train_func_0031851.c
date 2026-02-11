Read32(istream& ifs)
  {
    char ch;
    unsigned long val=0;
    for(int i=0; i<4; ++i)
    {
      if(!ifs.get(ch))
        return 0;
      val = val * 0x100 + (unsigned char)ch;
    }
    return val;
  }
