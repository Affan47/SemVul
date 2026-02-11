Append(const char *path)
{
  if( !System::FileIsDirectory(path) )
    {
    return false;
    }
  Internals->RessourcePaths.push_back( path );
  return true;
}
