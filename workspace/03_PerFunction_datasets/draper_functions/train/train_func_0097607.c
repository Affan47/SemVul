envz_add (char **envz, size_t *envz_len, const char *name, const char *value)
{
  envz_remove (envz, envz_len, name);

  if (value)

    {
      size_t name_len = strlen (name);
      size_t value_len = strlen (value);
      size_t old_envz_len = *envz_len;
      size_t new_envz_len = old_envz_len + name_len + 1 + value_len + 1;
      char *new_envz = realloc (*envz, new_envz_len);

      if (new_envz)
	{
	  memcpy (new_envz + old_envz_len, name, name_len);
	  new_envz[old_envz_len + name_len] = SEP;
	  memcpy (new_envz + old_envz_len + name_len + 1, value, value_len);
	  new_envz[new_envz_len - 1] = 0;

	  *envz = new_envz;
	  *envz_len = new_envz_len;

	  return 0;
	}
      else
	return ENOMEM;
    }
  else

    return __argz_add (envz, envz_len, name);
}
