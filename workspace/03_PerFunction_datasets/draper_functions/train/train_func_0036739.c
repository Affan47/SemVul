Open(const char* name)
{

  this->CleanUpFilesAndPath();

  DIR* dir = opendir(name);

  if (!dir)
    {
    return 0;
    }

  dirent* d =0;

  for (d = readdir(dir); d; d = readdir(dir))
    {
    this->Files->InsertNextValue(d->d_name);
    }
  this->Path = strcpy(new char[strlen(name)+1], name);

  closedir(dir);

  return 1;
}
