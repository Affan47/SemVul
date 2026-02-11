CheckArgumentKeyword(std::string const& arg)
{
  if(arg == "FILES")
    {
    this->ArgumentDoing = ArgumentDoingFiles;
    return true;
    }
  return false;
}
