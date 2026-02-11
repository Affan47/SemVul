_detailed_output_management_controller_confirmation_record (ipmi_sensors_state_data_t *state_data,
                                                            const void *sdr_record,
                                                            unsigned int sdr_record_len,
                                                            uint8_t record_type,
                                                            uint16_t record_id)
{
  uint16_t product_id;

  assert (state_data);
  assert (sdr_record);
  assert (sdr_record_len);
  assert (state_data->prog_data->args->verbose_count >= 2);

  if (_detailed_output_record_type_and_id (state_data,
                                           record_type,
                                           record_id) < 0)
    return (-1);

  if (_output_manufacturer_id (state_data,
                               sdr_record,
                               sdr_record_len) < 0)
    return (-1);

  if (ipmi_sdr_parse_product_id (state_data->sdr_parse_ctx,
                                 sdr_record,
                                 sdr_record_len,
                                 &product_id) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "ipmi_sdr_parse_product_id: %s\n",
                       ipmi_sdr_parse_ctx_errormsg (state_data->sdr_parse_ctx));
      return (-1);
    }

  pstdout_printf (state_data->pstate,
                  "Product ID: %Xh\n",
                  product_id);

  pstdout_printf (state_data->pstate, "\n");

  return (0);
}
