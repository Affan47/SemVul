MatchesFiles(const char* name)
{
  std::set<cmStdString>::const_iterator i = this->GroupFiles.find(name);
  if(i != this->GroupFiles.end())
    {
    return true;
    }
  return false;
}
