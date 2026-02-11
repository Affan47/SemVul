mkfilename(unsigned idx) const
    {
      std::string fname(_fname);
      fname += '.';
      fname += convert<std::string>(idx);
      return fname;
    }
