matches (const MatchType &type) const {
  if (type != *this)
    return false;
  MTNamed &matched_type = (MTNamed&)type;
  return _name.matches (matched_type._name) &&
    qual_matches (matched_type.qualified ());
}
