PrintImpl(EJournalCategory category, EJournalLevel level,
                              const char* str)
  {
    DBG_START_METH("Journal::Print", 0);
    if (file_) {
      fprintf(file_, "%s", str);
      DBG_EXEC(0, fflush(file_));
    }
  }
