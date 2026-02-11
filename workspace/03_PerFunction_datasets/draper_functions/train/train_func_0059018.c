set_preference_attribute(
  const char *username,
  const char *attr,
  const char *value)
{
  int i;

  if (username[0] == 0 || !strcmp(username, "default"))
    i = _ds_pref_set(agent_config, NULL, _ds_read_attribute(agent_config, "Home"), attr, value, NULL);
  else
    i = _ds_pref_set(agent_config, username, _ds_read_attribute(agent_config, "Home"), attr, value, NULL);

  if (!i)
    printf("operation successful.\n");
  else
    printf("operation failed with error %d.\n", i);

  return i;
}
