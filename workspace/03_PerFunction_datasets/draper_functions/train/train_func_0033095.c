clean_lookup(ParmString sl, WordEntry & o) const
{
  o.clear();
  pair<WordLookup::iterator, WordLookup::iterator> p(word_lookup->equal_range(sl));
  if (p.first == p.second) return false;
  o.what = WordEntry::Misspelled;
  set_word(o, *p.first);
  o.intr[0] = (void *)*p.first;
  return true;

}
