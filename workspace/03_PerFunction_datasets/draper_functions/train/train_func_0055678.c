conf_get_uint(const char * key, unsigned int * value_ptr)
{
  const char * str;

  if (!conf_get(key, &str))
  {
    return false;
  }

  return conf_string2uint(str, value_ptr);
}
