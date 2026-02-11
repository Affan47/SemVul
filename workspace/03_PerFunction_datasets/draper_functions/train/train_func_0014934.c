fnmatch_pattern_has_wildcards (const char *str, int options)
{
  const char *cset = "\\?*[]";
  if (options & FNM_NOESCAPE)
    cset++;
  while (*str)
    {
      size_t n = strcspn (str, cset);
      if (str[n] == 0)
        break;
      else if (str[n] == '\\')
        {
          str += n + 1;
          if (*str)
            str++;
        }
      else
        return true;
    }
  return false;
}
