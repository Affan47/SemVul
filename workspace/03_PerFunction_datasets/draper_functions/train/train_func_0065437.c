ucspi_getenv(const char* name)
{
  if (ucspi_protocol() == 0)
    return 0;
  strncpy(vartmp + protolen, name, MAXNAME);
  return getenv(vartmp);
}
