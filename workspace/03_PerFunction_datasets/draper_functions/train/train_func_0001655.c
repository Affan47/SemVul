_detailed_output_bmc_message_channel_info_record (ipmi_sensors_state_data_t *state_data,
                                                  const void *sdr_record,
                                                  unsigned int sdr_record_len,
                                                  uint8_t record_type,
                                                  uint16_t record_id)
{
  assert (state_data);
  assert (sdr_record);
  assert (sdr_record_len);
  assert (state_data->prog_data->args->verbose_count >= 2);

  if (_detailed_output_record_type_and_id (state_data,
                                           record_type,
                                           record_id) < 0)
    return (-1);

  pstdout_printf (state_data->pstate, "\n");

  return (0);
}
