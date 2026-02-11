setat(const int n, const char ch)
{
  if((!n)&&(!ptr))
  {
    init(GStringRep::Native::create(&ch,0,1));
  }else
  {
    init((*this)->setat(CheckSubscript(n),ch));
  }
}
