username_validate (const char *section_name,
                   const char *key_name,
                   const char *value,
                   void *arg)
{
  uint8_t userid;

  assert (section_name);
  assert (key_name);
  assert (value);

  userid = atoi (section_name + strlen ("User"));

  if (userid == 1)
    {
      if (!value || same (value, "null") || same (value, "anonymous"))
        return (CONFIG_VALIDATE_VALID_VALUE);
      else
        return (CONFIG_VALIDATE_INVALID_VALUE);
    }

  if (!value || strlen (value) > IPMI_MAX_USER_NAME_LENGTH)
    return (CONFIG_VALIDATE_INVALID_VALUE);
  return (CONFIG_VALIDATE_VALID_VALUE);
}
