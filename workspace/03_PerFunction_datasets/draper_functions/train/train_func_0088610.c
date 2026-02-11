config_yes_no_validate (const char *section_name,
                        const char *key_name,
                        const char *value,
                        void *arg)
{
  assert (section_name);
  assert (key_name);
  assert (value);

  if (!strcasecmp (value, "yes") || !strcasecmp (value, "no"))
    return (CONFIG_VALIDATE_VALID_VALUE);
  return (CONFIG_VALIDATE_INVALID_VALUE);
}
