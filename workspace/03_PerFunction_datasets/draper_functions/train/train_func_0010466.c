CopyFileAlways(const char* source, const char* destination,
                                 bool copyPermissions)
{

  if ( SystemTools::SameFile(source, destination) )
    {
    return true;
    }
  mode_t perm = 0;
  bool perms = SystemTools::GetPermissions(source, perm);

  const int bufferSize = 4096;
  char buffer[bufferSize];


  kwsys_stl::string new_destination;
  if(SystemTools::FileExists(destination) &&
     SystemTools::FileIsDirectory(destination))
    {
    new_destination = destination;
    SystemTools::ConvertToUnixSlashes(new_destination);
    new_destination += '/';
    kwsys_stl::string source_name = source;
    new_destination += SystemTools::GetFilenameName(source_name);
    destination = new_destination.c_str();
    }


  kwsys_stl::string destination_dir = destination;
  destination_dir = SystemTools::GetFilenamePath(destination_dir);
  SystemTools::MakeDirectory(destination_dir.c_str());


#if defined(_WIN32) || defined(__CYGWIN__)
  kwsys_ios::ifstream fin(source,
                    kwsys_ios::ios::binary | kwsys_ios::ios::in);
#else
  kwsys_ios::ifstream fin(source);
#endif
  if(!fin)
    {
    return false;
    }


  SystemTools::RemoveFile(destination);

#if defined(_WIN32) || defined(__CYGWIN__)
  kwsys_ios::ofstream fout(destination,
                     kwsys_ios::ios::binary | kwsys_ios::ios::out | kwsys_ios::ios::trunc);
#else
  kwsys_ios::ofstream fout(destination,
                     kwsys_ios::ios::out | kwsys_ios::ios::trunc);
#endif
  if(!fout)
    {
    return false;
    }


  while(fin)
    {
    fin.read(buffer, bufferSize);
    if(fin.gcount())
      {
      fout.write(buffer, fin.gcount());
      }
    }


  fout.flush();

  fin.close();
  fout.close();


  struct stat statSource, statDestination;
  statSource.st_size = 12345;
  statDestination.st_size = 12345;
  if(stat(source, &statSource) != 0)
    {
    return false;
    }
  else if(stat(destination, &statDestination) != 0)
    {
    return false;
    }
  else if(statSource.st_size != statDestination.st_size)
    {
   return false;
    }
  if ( copyPermissions && perms )
    {
    if ( !SystemTools::SetPermissions(destination, perm) )
      {
      return false;
      }
    }
  return true;
}
