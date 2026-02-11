session_env_list_stdenvnames (int *iterator, const char **r_assname)
{
  int idx = *iterator;

  if (idx < 0 || idx >= DIM (stdenvnames))
    return NULL;
  *iterator = idx + 1;
  if (r_assname)
    *r_assname = stdenvnames[idx].assname;
  return stdenvnames[idx].name;
}
