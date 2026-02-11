threshold_event_enable_checkout (const char *section_name,
                                 struct config_keyvalue *kv,
                                 void *arg)
{
  ipmi_sensors_config_state_data_t *state_data;
  struct sensor_event_enable_data data;
  uint16_t bits = 0;
  uint8_t bitposition = 0;
  config_err_t rv = CONFIG_ERR_FATAL_ERROR;
  config_err_t ret;

  assert (section_name);
  assert (kv);
  assert (arg);

  state_data = (ipmi_sensors_config_state_data_t *)arg;

  if ((ret = _threshold_event_enable_verify (state_data,
                                             section_name)) != CONFIG_ERR_SUCCESS)
    {
      rv = ret;
      goto cleanup;
    }

  if ((ret = _threshold_event_enable_get_data (state_data,
                                               section_name,
                                               kv,
                                               &data,
                                               &bits,
                                               &bitposition)) != CONFIG_ERR_SUCCESS)
    {
      rv = ret;
      goto cleanup;
    }

  if (config_section_update_keyvalue_output (state_data->pstate,
                                             kv,
                                             ((bits >> bitposition) & 0x1) ? "Yes" : "No") < 0)
    goto cleanup;

  rv = CONFIG_ERR_SUCCESS;
 cleanup:
  return (rv);
}
