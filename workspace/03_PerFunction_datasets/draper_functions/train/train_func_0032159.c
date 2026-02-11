_ipmimonitoring_legacy_simple_output_compact_record (ipmi_sensors_state_data_t *state_data,
                                                     const void *sdr_record,
                                                     unsigned int sdr_record_len,
                                                     uint16_t record_id,
                                                     int event_message_output_type,
                                                     uint16_t sensor_event_bitmask,
                                                     char **event_message_list,
                                                     unsigned int event_message_list_len)
{
  assert (state_data);
  assert (sdr_record);
  assert (sdr_record_len);
  assert (IPMI_SENSORS_EVENT_VALID (event_message_output_type));

  if (_ipmimonitoring_legacy_simple_output_header (state_data,
                                                   sdr_record,
                                                   sdr_record_len,
                                                   record_id) < 0)
    return (-1);

  if (state_data->prog_data->args->output_sensor_state)
    {
      char *sensor_state_str = NULL;

      if (ipmi_sensors_get_sensor_state (state_data,
					 sdr_record,
					 sdr_record_len,
					 event_message_output_type,
					 sensor_event_bitmask,
					 &sensor_state_str) < 0)
	return (-1);

      pstdout_printf (state_data->pstate,
		      " | %s",
		      sensor_state_str);
    }

  if (state_data->prog_data->args->quiet_readings)
    return (0);

  pstdout_printf (state_data->pstate,
		  " | %s | ",
		  IPMIMONITORING_NA_STRING_LEGACY);

  if (ipmi_sensors_output_event_message_list (state_data,
                                              event_message_output_type,
                                              sensor_event_bitmask,
                                              event_message_list,
                                              event_message_list_len,
                                              NULL,
                                              0) < 0)
    return (-1);

  return (0);
}
