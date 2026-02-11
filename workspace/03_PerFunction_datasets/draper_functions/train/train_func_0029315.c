PrintImplOffset(const Journalist& jnlst,
                                   EJournalLevel level,
                                   EJournalCategory category,
                                   const std::string& name,
                                   Index indent,
                                   const std::string& prefix,
                                   Index offset) const
  {
    jnlst.Printf(level, category, "\n");
    jnlst.PrintfIndented(level, category, indent,
                         "%sGenTMatrix \"%s\" of dimension %d by %d with %d nonzero elements:\n",
                         prefix.c_str(), name.c_str(), NRows(), NCols(), Nonzeros());
    if (initialized_) {
      for (Index i=0; i<Nonzeros(); i++) {
        jnlst.PrintfIndented(level, category, indent,
                             "%s%s[%5d,%5d]=%23.16e  (%d)\n",
                             prefix.c_str(), name.c_str(), Irows()[i]+offset,
                             Jcols()[i], values_[i], i);
      }
    }
    else {
      jnlst.PrintfIndented(level, category, indent,
                           "%sUninitialized!\n", prefix.c_str());
    }
  }
