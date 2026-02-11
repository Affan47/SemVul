emit(raw_ostream &o, unsigned int &i) {
      unsigned int index;
      unsigned int numFlags = Flags.size();
      if (numFlags == 0)
        o << "0";

      for (index = 0; index < numFlags; ++index) {
        o << Flags[index].c_str();
        if (index < (numFlags - 1))
          o << " | ";
      }
    }
