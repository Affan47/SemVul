qual_matches (const MTQual *qual) const {
  if (!qual && is_qualified ())
    return false;
  if (qual) {
    if (_const && !qual->is_const ())
        return false;
    if (_volatile && !qual->is_volatile ())
        return false;
  }
  return true;
}
