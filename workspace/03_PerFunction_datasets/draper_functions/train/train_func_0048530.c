check_file(string filename, bool write_check)
{
  if(filename == "")
    return 0;

  struct stat config_stat;

  if(!stat( filename.c_str(), &config_stat) && config_stat.st_mode & S_IFREG)
  {
    fstream config( filename.c_str() , ios_base::in);

    if(config)
    {
      config.close();

      if(write_check)
      {
        config.open(filename.c_str(), ios_base::out | ios_base::app);
        if(!config)
          return 0;
        config.close();
      }

      return 1;
    }
  }

  return 0;
}
