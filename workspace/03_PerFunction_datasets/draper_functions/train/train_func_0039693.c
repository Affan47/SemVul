directory_name (string file)
{
  int pos = file.rfind ('/');
  if (pos == -1)
    return ".";
  else
    return file.substr (0, pos);
}
