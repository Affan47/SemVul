eventSpecial (int key)
{
  char buf [256];
  if (!active) return;
  if (highlight)
  {
    key2string (key + 256, buf);
    if (buf [0] != '\0')
    {
      this->special = key;
      specialActive = true;
      execFunction (special + 256);
    }
  }
}
