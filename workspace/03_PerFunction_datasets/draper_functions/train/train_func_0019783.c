init(void)
{
  int len;
  DIR *dir;
  struct stat statbuf;
  struct dirent *entry;
  char *dirname, *filename;

  if (kcemu_homedir == NULL)
    return;

  _addr = 0x0100;

  _ram[0] = _port;
  _ram[1] = 0;
  _ram[2] = 0;

  len = strlen(kcemu_homedir) + 21;
  dirname = new char[len];
  snprintf(dirname, len, "%s/.z1013-ramfloppy_%02x", kcemu_homedir, _port & 0xff);

  dir = opendir(dirname);
  if (dir == NULL)
    {
      delete[] dirname;
      return;
    }

  while (242)
    {
      entry = readdir(dir);
      if (entry == NULL)
	break;

      len = strlen(dirname) + strlen(entry->d_name) + 2;
      filename = new char[len];
      snprintf(filename, len, "%s/%s", dirname, entry->d_name);

      if (stat(filename, &statbuf) == 0)
	if (S_ISREG(statbuf.st_mode))
	  read_file(filename, statbuf.st_size);

      delete[] filename;
    }

  closedir(dir);
  delete[] dirname;
}
