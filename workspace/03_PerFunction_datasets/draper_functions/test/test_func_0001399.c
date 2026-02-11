k_g_checkout (const char *section_name,
              struct config_keyvalue *kv,
              void *arg)
{
  bmc_config_state_data_t *state_data;
  uint8_t k_g[IPMI_MAX_K_G_LENGTH];
  char k_g_str[IPMI_MAX_K_G_LENGTH*2+3];
  config_err_t ret;

  assert (section_name);
  assert (kv);
  assert (arg);

  state_data = (bmc_config_state_data_t *)arg;

  memset (k_g, 0, IPMI_MAX_K_G_LENGTH);

  if ((ret = _get_key (state_data,
		       section_name,
                       IPMI_CHANNEL_SECURITY_KEYS_KEY_ID_K_G,
                       k_g,
                       IPMI_MAX_K_G_LENGTH)) != CONFIG_ERR_SUCCESS)
    return (ret);


  if (state_data->prog_data->args->config_args.action == CONFIG_ACTION_DIFF)
    {
      uint8_t kv_k_g[IPMI_MAX_K_G_LENGTH+1];

      memset (kv_k_g, '\0', IPMI_MAX_K_G_LENGTH);
      if (parse_kg (kv_k_g, IPMI_MAX_K_G_LENGTH + 1, kv->value_input) < 0)
        return (CONFIG_ERR_FATAL_ERROR);

      if (!memcmp (kv_k_g, k_g, IPMI_MAX_K_G_LENGTH))
        {
          if (config_section_update_keyvalue_output (state_data->pstate,
                                                     kv,
                                                     kv->value_input) < 0)
            return (CONFIG_ERR_FATAL_ERROR);

          return (CONFIG_ERR_SUCCESS);
        }

    }

  memset (k_g_str, '\0', IPMI_MAX_K_G_LENGTH*2+3);
  if (!format_kg (k_g_str, IPMI_MAX_K_G_LENGTH*2+3, k_g))
    return (CONFIG_ERR_FATAL_ERROR);

  if (config_section_update_keyvalue_output (state_data->pstate,
                                             kv,
                                             k_g_str) < 0)
    return (CONFIG_ERR_FATAL_ERROR);

  return (CONFIG_ERR_SUCCESS);
}
