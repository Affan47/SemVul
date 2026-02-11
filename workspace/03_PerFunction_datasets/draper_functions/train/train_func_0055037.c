contains_match(const Match &m) const
{
  matches_iterator iter;
  iter = _matches.find(m.get_top_pos());

  if (iter == _matches.end()) {
    return false;
  }

  const _MatchContainer * cont = iter->second;


  for (unsigned int i = 0; i < cont->num; i++) {
    const Match * this_m = (const Match *) &cont->block[i];
    if (this_m->equals(&m)) {
      return true;
    }
  }

  return false;
}
