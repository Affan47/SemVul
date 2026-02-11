_ipmi_oem_quanta_set_extended_config_value (ipmi_oem_state_data_t *state_data,
                                            uint8_t configuration_id,
                                            uint8_t attribute_id,
                                            uint8_t index,
                                            unsigned int value_length,
                                            uint32_t value)
{
  uint8_t bytes_rq[IPMI_OEM_MAX_BYTES];
  uint8_t bytes_rs[IPMI_OEM_MAX_BYTES];
  int rs_len;
  uint8_t reservation_id;
  int rv = -1;

  assert (state_data);
  assert (value_length == 1
          || value_length == 2
          || value_length == 4);


  if (_quanta_get_reservation (state_data,
                               &reservation_id) < 0)
    goto cleanup;

  bytes_rq[0] = IPMI_CMD_OEM_QUANTA_SET_EXTENDED_CONFIGURATION;
  bytes_rq[1] = reservation_id;
  bytes_rq[2] = configuration_id;
  bytes_rq[3] = attribute_id;
  bytes_rq[4] = index;
  bytes_rq[5] = 0x00;
  bytes_rq[6] = 0x00;
  bytes_rq[7] = 0x01;

  if (value_length == 1)
    bytes_rq[8] = (value & 0x000000FF);
  else if (value_length == 2)
    {
      bytes_rq[8] = (value & 0x000000FF);
      bytes_rq[9] = (value & 0x0000FF00) >> 8;
    }
  else
    {
      bytes_rq[8] = (value & 0x000000FF);
      bytes_rq[9] = (value & 0x0000FF00) >> 8;
      bytes_rq[10] = (value & 0x00FF0000) >> 16;
      bytes_rq[11] = (value & 0xFF000000) >> 24;
    }

  if ((rs_len = ipmi_cmd_raw (state_data->ipmi_ctx,
                              0,
                              IPMI_NET_FN_OEM_QUANTA_GENERIC_RQ,
                              bytes_rq,
                              8 + value_length,
                              bytes_rs,
                              IPMI_OEM_MAX_BYTES)) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "ipmi_cmd_raw: %s\n",
                       ipmi_ctx_errormsg (state_data->ipmi_ctx));
      goto cleanup;
    }

  if (ipmi_oem_check_response_and_completion_code (state_data,
                                                   bytes_rs,
                                                   rs_len,
                                                   2,
                                                   IPMI_CMD_OEM_QUANTA_SET_EXTENDED_CONFIGURATION,
                                                   IPMI_NET_FN_OEM_QUANTA_GENERIC_RS,
                                                   NULL) < 0)
    goto cleanup;

  rv = 0;
 cleanup:
  return (rv);
}
