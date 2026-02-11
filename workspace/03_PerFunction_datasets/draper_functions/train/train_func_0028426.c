OrStrings(set<string>* ss) {
  SimplifyStringSet(ss);
  Prefilter* or_prefilter = NULL;
  if (!ss->empty()) {
    or_prefilter = new Prefilter(NONE);
    for (SSIter i = ss->begin(); i != ss->end(); ++i)
      or_prefilter = Or(or_prefilter, FromString(*i));
  }
  return or_prefilter;
}
