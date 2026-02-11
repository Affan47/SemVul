_ipmimonitoring_legacy_simple_output_header (ipmi_sensors_state_data_t *state_data,
                                             const void *sdr_record,
                                             unsigned int sdr_record_len,
                                             uint16_t record_id)
{
  char id_string[IPMI_SDR_CACHE_MAX_ID_STRING + 1];
  uint8_t sensor_type;
  uint8_t event_reading_type_code;
  const char * sensor_type_string = NULL;

  assert (state_data);
  assert (sdr_record);
  assert (sdr_record_len);

  memset (id_string, '\0', IPMI_SDR_CACHE_MAX_ID_STRING + 1);

  if (ipmi_sdr_parse_id_string (state_data->sdr_parse_ctx,
                                sdr_record,
                                sdr_record_len,
                                id_string,
                                IPMI_SDR_CACHE_MAX_ID_STRING) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "ipmi_sdr_parse_id_string: %s\n",
                       ipmi_sdr_parse_ctx_errormsg (state_data->sdr_parse_ctx));
      return (-1);
    }

  if (ipmi_sdr_parse_sensor_type (state_data->sdr_parse_ctx,
                                  sdr_record,
                                  sdr_record_len,
                                  &sensor_type) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "ipmi_sdr_parse_sensor_type: %s\n",
                       ipmi_sdr_parse_ctx_errormsg (state_data->sdr_parse_ctx));
      return (-1);
    }

  if ((state_data->prog_data->args->interpret_oem_data)
      && (ipmi_sdr_parse_event_reading_type_code (state_data->sdr_parse_ctx,
                                                  sdr_record,
                                                  sdr_record_len,
                                                  &event_reading_type_code) >= 0))
    sensor_type_string = get_oem_sensor_type_output_string (sensor_type,
                                                            event_reading_type_code,
                                                            state_data->oem_data.manufacturer_id,
                                                            state_data->oem_data.product_id);
  else
    sensor_type_string = get_sensor_type_output_string (sensor_type);

  pstdout_printf (state_data->pstate,
                  "%u | %s | %s",
                  record_id,
                  id_string,
                  sensor_type_string);

  return (0);
}
