gap_base_dup_filename_and_replace_extension_by_underscore(const char *filename)
{
  int l_len;
  int l_idx;
  char *l_str;
  char *l_nameWithUnderscore;

  if(filename == NULL)
  {
    return (g_strdup("_"));
  }

  l_len = strlen(filename);
  l_str = g_strdup(filename);


  for(l_idx = l_len -1; l_idx >= 0; l_idx--)
  {
    if (l_str[l_idx] == '.')
    {
      l_str[l_idx] = '\0';
      break;
    }
  }


  l_nameWithUnderscore = gap_base_strdup_add_underscore(l_str);

  g_free(l_str);

  return (l_nameWithUnderscore);

}
