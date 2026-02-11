str()
{
  if(!this->Result)
    {
    std::string s = static_cast<ostringstream*>(&this->ostr)->str();
    this->Result = new char[s.length()+1];
    strcpy(this->Result, s.c_str());
    this->freeze();
    }
  return this->Result;
}
