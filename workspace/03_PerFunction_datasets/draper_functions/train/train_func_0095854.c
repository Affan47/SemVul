ipmi_oem_intel_set_power_restore_delay (ipmi_oem_state_data_t *state_data)
{
  uint8_t bytes_rq[IPMI_OEM_MAX_BYTES];
  uint8_t bytes_rs[IPMI_OEM_MAX_BYTES];
  unsigned int tmp;
  char *endptr;
  uint16_t delay = 0;
  int rs_len;
  int rv = -1;

  assert (state_data);
  assert (state_data->prog_data->args->oem_options_count == 1);

  errno = 0;

  tmp = strtoul (state_data->prog_data->args->oem_options[0],
		 &endptr,
		 10);
  if (errno
      || endptr[0] != '\0'
      || tmp > IPMI_OEM_INTEL_POWER_RESTORE_DELAY_MAX)
    {
      pstdout_fprintf (state_data->pstate,
		       stderr,
		       "%s:%s invalid OEM option argument '%s'\n",
		       state_data->prog_data->args->oem_id,
		       state_data->prog_data->args->oem_command,
		       state_data->prog_data->args->oem_options[0]);
      goto cleanup;
    }

  delay = tmp;


  bytes_rq[0] = IPMI_CMD_OEM_INTEL_SET_POWER_RESTORE_DELAY;
  bytes_rq[1] = (delay & IPMI_OEM_INTEL_POWER_RESTORE_DELAY_MSB_MASK) >> 8;
  bytes_rq[2] = (delay & IPMI_OEM_INTEL_POWER_RESTORE_DELAY_LSB_MASK);

  if ((rs_len = ipmi_cmd_raw (state_data->ipmi_ctx,
                              0,
                              IPMI_NET_FN_OEM_INTEL_GENERIC_RQ,
                              bytes_rq,
                              3,
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
                                                   IPMI_CMD_OEM_INTEL_SET_POWER_RESTORE_DELAY,
                                                   IPMI_NET_FN_OEM_INTEL_GENERIC_RS,
                                                   NULL) < 0)
    goto cleanup;

  rv = 0;
 cleanup:
  return (rv);
}
