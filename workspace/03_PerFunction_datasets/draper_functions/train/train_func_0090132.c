CanWriteFile(const char *fname)
{
  std::string filename = fname;

  if ( filename.length() > 4
       && ( filename.find(".mrc") == filename.length() - 4
            || filename.find(".rec") == filename.length() - 4 ) )
    {
    return true;
    }
  return false;
}
