caml_executable_name(char * name, int name_len)
{
  int retcode;
  struct stat st;

  retcode = readlink("/proc/self/exe", name, name_len);
  if (retcode == -1 || retcode >= name_len) return -1;
  name[retcode] = 0;


  if (stat(name, &st) != 0) return -1;
  if (! S_ISREG(st.st_mode)) return -1;
  return 0;
}
