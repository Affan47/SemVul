operator+(const GUTF8String &s2) const
{
  if (ptr)
    return GStringRep::UTF8::create((*this)->toUTF8(true),s2);
  else
    return GStringRep::UTF8::create((*this),s2);
}
