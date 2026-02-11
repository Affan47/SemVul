processPattern(const MSString& aPattern_)
{
  unsigned startPos=_patternPosition+_patternLength;
  _patternPosition=_parseText.indexOf(aPattern_,startPos);

  if (_patternPosition<_parseText.length())
   {
     _patternLength=aPattern_.length();
     if (_tokenCount>0) reparseTokens(startPos,_patternPosition);
   }
  else
   {
     _patternPosition=_parseText.length();
     _patternLength=0;
   }

  _currentPosition=_patternPosition+_patternLength;
  clearSavedTokens();

  return *this;
}
