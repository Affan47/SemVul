writeFile(QString fname, bool rename)
{
  QFile file(fname);
  return writeFile(file, rename);
}
