operator+= (const GBaseString &str)
{
  return init(GStringRep::UTF8::create(*this,str));
}
