sinThetaN(const unsigned int n) const {
  WAMap::const_iterator pos = theMixingAngles.find(n);
  if(pos != theMixingAngles.end())
    return pos->second;
  else {
    throw Exception() << "UEDBase::sinThetaN() - A mixing angle has "
		      << "been requested for a level that does not "
		      << "exist. Check that the radiative corrections "
		      << "for the " << n << "th level have been "
		      << "calculated." << Exception::warning;
    return 0.0;
  }
}
