del_preference_attribute(
  const char *username,
  const char *attr)
{
  int i;

  if (username[0] == 0 || !strncmp(username, "default", strlen(username)))
    i = _ds_pref_del(agent_config, NULL, _ds_read_attribute(agent_config, "Home"), attr, NULL);
  else
    i = _ds_pref_del(agent_config, username, _ds_read_attribute(agent_config, "Home"), attr, NULL);

  if (!i)
    printf("operation successful.\n");
  else
    printf("operation failed with error %d.\n", i);

  return i;
}
