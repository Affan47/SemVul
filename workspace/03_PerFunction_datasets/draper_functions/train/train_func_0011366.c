lookup(ParmString word, const SensitiveCompare * c,
                              WordEntry & o) const
{
  o.clear();
  pair<WordLookup::iterator, WordLookup::iterator> p(word_lookup->equal_range(word));
  while (p.first != p.second) {
    if ((*c)(word,*p.first)) {
      o.what = WordEntry::Misspelled;
      set_word(o, *p.first);
      o.intr[0] = (void *)*p.first;
      return true;
    }
    ++p.first;
  }
  return false;
}
