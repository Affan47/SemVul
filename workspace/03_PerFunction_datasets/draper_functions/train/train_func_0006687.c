k_g_validate (const char *section_name,
              const char *key_name,
              const char *value,
              void *arg)
{
  uint8_t k_g[IPMI_MAX_K_G_LENGTH+1];

  assert (section_name);
  assert (key_name);
  assert (value);

  if (parse_kg (k_g, IPMI_MAX_K_G_LENGTH + 1, value) < 0)
    return (CONFIG_VALIDATE_INVALID_VALUE);
  return (CONFIG_VALIDATE_VALID_VALUE);
}
