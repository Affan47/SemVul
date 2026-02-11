_ipmi_oem_quanta_set_extended_config_string (ipmi_oem_state_data_t *state_data,
                                             uint8_t configuration_id,
                                             uint8_t attribute_id,
                                             uint8_t index,
                                             char *buf,
                                             unsigned int buflen)
{
  uint8_t bytes_rq[IPMI_OEM_MAX_BYTES];
  uint8_t bytes_rs[IPMI_OEM_MAX_BYTES];
  int rs_len;
  uint8_t reservation_id;
  int rv = -1;

  assert (state_data);
  assert (buf);


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
  bytes_rq[8] = strlen (buf);

  if (buflen)
    memcpy (&bytes_rq[9], buf, buflen);

  if ((rs_len = ipmi_cmd_raw (state_data->ipmi_ctx,
                              0,
                              IPMI_NET_FN_OEM_QUANTA_GENERIC_RQ,
                              bytes_rq,
                              9 + buflen,
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
