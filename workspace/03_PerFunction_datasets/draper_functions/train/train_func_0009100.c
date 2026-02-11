version_set_to_null (version_t version)
{
  size_t n;

  for (n = 0 ; n < VERSION_LENGTH ; n++)
    version[n] = 0;
}
