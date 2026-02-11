capab_search(const char *key, const struct capabilities *cap)
{
  const char *rb = cap->name;

  while (ToLower(*key) == ToLower(*rb))
    if (*key++ == '\0')
      return 0;
    else
      rb++;


  return (IsSpace(*key) && *rb == '\0') ? 0 : (ToLower(*key) - ToLower(*rb));
}
