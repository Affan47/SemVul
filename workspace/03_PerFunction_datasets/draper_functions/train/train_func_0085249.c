_detailed_output_fru_device_locator_record (ipmi_sensors_state_data_t *state_data,
                                            const void *sdr_record,
                                            unsigned int sdr_record_len,
                                            uint8_t record_type,
                                            uint16_t record_id)
{
  uint8_t device_access_address;
  uint8_t logical_fru_device_device_slave_address;
  uint8_t private_bus_id;
  uint8_t lun_for_master_write_read_fru_command;
  uint8_t logical_physical_fru_device;
  uint8_t channel_number;
  uint8_t fru_entity_id;
  uint8_t fru_entity_instance;

  assert (state_data);
  assert (sdr_record);
  assert (sdr_record_len);
  assert (state_data->prog_data->args->verbose_count >= 2);

  if (_detailed_output_header2 (state_data,
                                sdr_record,
                                sdr_record_len,
                                record_type,
                                record_id) < 0)
    return (-1);

  if (ipmi_sdr_parse_fru_device_locator_parameters (state_data->sdr_parse_ctx,
                                                    sdr_record,
                                                    sdr_record_len,
                                                    &device_access_address,
                                                    &logical_fru_device_device_slave_address,
                                                    &private_bus_id,
                                                    &lun_for_master_write_read_fru_command,
                                                    &logical_physical_fru_device,
                                                    &channel_number) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "ipmi_sdr_parse_generic_device_locator_parameters: %s\n",
                       ipmi_sdr_parse_ctx_errormsg (state_data->sdr_parse_ctx));

      return (-1);
    }

  pstdout_printf (state_data->pstate,
                  "Device Access Address: %Xh\n",
                  device_access_address);

  if (logical_physical_fru_device)
    pstdout_printf (state_data->pstate,
                    "FRU Device ID: %Xh\n",
                    logical_fru_device_device_slave_address);
  else
    pstdout_printf (state_data->pstate,
                    "Device Slave Address: %Xh\n",
                    logical_fru_device_device_slave_address);

  pstdout_printf (state_data->pstate,
                  "Private Bus ID: %Xh\n",
                  private_bus_id);

  pstdout_printf (state_data->pstate,
                  "LUN for Master Write-Read or FRU Command: %Xh\n",
                  lun_for_master_write_read_fru_command);

  pstdout_printf (state_data->pstate,
                  "Channel Number: %Xh\n",
                  channel_number);

  if (_output_device_type_and_modifier (state_data,
                                        sdr_record,
                                        sdr_record_len) < 0)
    return (-1);

  if (ipmi_sdr_parse_fru_entity_id_and_instance (state_data->sdr_parse_ctx,
                                                 sdr_record,
                                                 sdr_record_len,
                                                 &fru_entity_id,
                                                 &fru_entity_instance) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "ipmi_sdr_parse_fru_entity_id_and_instance: %s\n",
                       ipmi_sdr_parse_ctx_errormsg (state_data->sdr_parse_ctx));
      return (-1);
    }

  if (_detailed_output_entity_id_and_instance (state_data,
                                               "FRU",
                                               fru_entity_id,
                                               fru_entity_instance) < 0)
    return (-1);

  pstdout_printf (state_data->pstate, "\n");

  return (0);
}
