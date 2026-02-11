boot_device_checkout (const char *section_name,
                      struct config_keyvalue *kv,
                      void *arg)
{
  ipmi_chassis_config_state_data_t *state_data;
  struct boot_flags_data data;
  config_err_t ret;

  assert (section_name);
  assert (kv);
  assert (arg);

  state_data = (ipmi_chassis_config_state_data_t *)arg;

  if ((ret = _get_boot_flags (state_data, &data)) != CONFIG_ERR_SUCCESS)
    return (ret);

  if (config_section_update_keyvalue_output (state_data->pstate,
                                             kv,
                                             boot_device_string (data.boot_device)) < 0)
    return (CONFIG_ERR_FATAL_ERROR);

  return (CONFIG_ERR_SUCCESS);
}
