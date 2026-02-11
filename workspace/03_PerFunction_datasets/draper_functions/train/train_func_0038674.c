taglib_tag_free_strings()
{
  if(!stringManagementEnabled)
    return;

  for(List<char *>::Iterator it = strings.begin(); it != strings.end(); ++it)
    free(*it);
  strings.clear();
}
