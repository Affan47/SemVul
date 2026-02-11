_floating_point_in_range (const char *section_name,
                          const char *key_name,
                          const char *value,
                          double value_input,
                          void *arg)
{
  ipmi_sensors_config_state_data_t *state_data;
  uint8_t sdr_record[IPMI_SDR_CACHE_MAX_SDR_RECORD_LENGTH];
  unsigned int sdr_record_len = IPMI_SDR_CACHE_MAX_SDR_RECORD_LENGTH;
  config_validate_t rv = CONFIG_VALIDATE_FATAL_ERROR;
  config_err_t ret;
  uint8_t threshold_raw;
  uint8_t sensor_number;
  double threshold_calc;
  double threshold_range_min, threshold_range_max;

  assert (section_name);
  assert (key_name);
  assert (value);
  assert (arg);

  state_data = (ipmi_sensors_config_state_data_t *)arg;

  if ((ret = get_sdr_record (state_data,
                             section_name,
                             sdr_record,
                             &sdr_record_len)) != CONFIG_ERR_SUCCESS)
    {
      if (ret == CONFIG_ERR_NON_FATAL_ERROR)
        rv = CONFIG_VALIDATE_NON_FATAL_ERROR;
      goto cleanup;
    }

  if (ipmi_sdr_parse_sensor_number (state_data->sdr_parse_ctx,
                                    sdr_record,
                                    sdr_record_len,
                                    &sensor_number) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "ipmi_sdr_parse_sensor_number: %s\n",
                       ipmi_sdr_parse_ctx_errormsg (state_data->sdr_parse_ctx));
      goto cleanup;
    }

  if ((ret = _decode_value_raw (state_data,
                                sdr_record,
                                sdr_record_len,
                                value,
                                &threshold_raw)) != CONFIG_ERR_SUCCESS)
    {
      if (ret == CONFIG_ERR_NON_FATAL_ERROR)
        rv = CONFIG_VALIDATE_NON_FATAL_ERROR;
      goto cleanup;
    }

  if ((ret = _decode_value (state_data,
                            sdr_record,
                            sdr_record_len,
                            threshold_raw,
                            &threshold_calc)) != CONFIG_ERR_SUCCESS)
    {
      if (ret == CONFIG_ERR_NON_FATAL_ERROR)
        rv = CONFIG_VALIDATE_NON_FATAL_ERROR;
      goto cleanup;
    }

  threshold_range_min = threshold_calc * THRESHOLD_RANGE_MIN_MULTIPLIER;
  threshold_range_max = threshold_calc * THRESHOLD_RANGE_MAX_MULTIPLIER;


  if ((value_input >= 0.0
       && (value_input < threshold_range_min
           || value_input > threshold_range_max))
      || (value_input < 0.0
          && (value_input > threshold_range_min
              || value_input < threshold_range_max)))
    rv = CONFIG_VALIDATE_OUT_OF_RANGE_VALUE;
  else
    rv = CONFIG_VALIDATE_VALID_VALUE;

 cleanup:
  return (rv);
}
