defineId(const StringC &str, const Location &loc,
			      Location &prevLoc)
{
  if (!inInstance() || !validate())
    return 1;
  Id *id = lookupCreateId(str);
  if (id->defined()) {
    prevLoc = id->defLocation();
    return 0;
  }
  id->define(loc);
  return 1;
}
