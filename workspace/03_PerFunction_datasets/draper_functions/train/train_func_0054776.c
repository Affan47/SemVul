fileExists(const char* file)
{
  ifstream fs(file);
  if (!fs)
  {
    return false;
  }
  fs.close();

  return true;
}
