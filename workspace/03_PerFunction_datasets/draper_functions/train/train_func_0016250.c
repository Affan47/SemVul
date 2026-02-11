InsertRuleLauncher(std::string& s, cmTarget* target,
                                          const char* prop)
{
  if(const char* val = this->GetRuleLauncher(target, prop))
    {
    cmOStringStream wrapped;
    wrapped << val << " " << s;
    s = wrapped.str();
    }
}
