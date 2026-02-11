GetCWD()
{
  jalib::string cwd;
  char buf[PATH_MAX];
  JASSERT(getcwd(buf, PATH_MAX) == buf)
    .Text("Pathname too long");
  cwd = buf;
  return cwd;
}
