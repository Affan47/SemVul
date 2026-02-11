reverse_top_matches() const
{
  MutableComparison new_cmp(_top_length, _bottom_length, _windowsize);

  matches_iterator iter;

  for (iter = _matches.begin(); iter != _matches.end(); iter++) {
    _MatchContainer * cont = iter->second;

    for (unsigned int i = 0; i < cont->num; i++) {
      Match * m = &cont->block[i];
      Match * new_m = m->copy();
      new_m->reverse_top(_top_length, _bottom_length);

      new_cmp.add_match(new_m);
    }
  }

  return new ImmutableComparison(&new_cmp);
}
