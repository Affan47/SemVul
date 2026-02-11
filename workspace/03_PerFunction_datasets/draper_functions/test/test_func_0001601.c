secondary_rmcp_port_checkout (const char *section_name,
                              struct config_keyvalue *kv,
                              void *arg)
{
  bmc_config_state_data_t *state_data;
  fiid_obj_t obj_cmd_rs = NULL;
  uint16_t secondary_rmcp_port_number;
  uint64_t val;
  config_err_t rv = CONFIG_ERR_FATAL_ERROR;
  config_err_t ret;
  uint8_t channel_number;

  assert (section_name);
  assert (kv);
  assert (arg);

  state_data = (bmc_config_state_data_t *)arg;

  if (!(obj_cmd_rs = fiid_obj_create (tmpl_cmd_get_lan_configuration_parameters_secondary_rmcp_port_number_rs)))
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_create: %s\n",
                       strerror (errno));
      goto cleanup;
    }

  if ((ret = get_lan_channel_number (state_data, section_name, &channel_number)) != CONFIG_ERR_SUCCESS)
    {
      rv = ret;
      goto cleanup;
    }

  if (ipmi_cmd_get_lan_configuration_parameters_secondary_rmcp_port_number (state_data->ipmi_ctx,
                                                                            channel_number,
                                                                            IPMI_GET_SOL_PARAMETER,
                                                                            IPMI_LAN_CONFIGURATION_PARAMETERS_NO_SET_SELECTOR,
                                                                            IPMI_LAN_CONFIGURATION_PARAMETERS_NO_BLOCK_SELECTOR,
                                                                            obj_cmd_rs) < 0)
    {
      if (state_data->prog_data->args->config_args.common.debug)
        pstdout_fprintf (state_data->pstate,
                         stderr,
                         "ipmi_cmd_get_lan_configuration_parameters_secondary_rmcp_port_number: %s\n",
                         ipmi_ctx_errormsg (state_data->ipmi_ctx));

      if (config_is_config_param_non_fatal_error (state_data->ipmi_ctx,
                                                  obj_cmd_rs,
                                                  &ret))
        rv = ret;

      goto cleanup;
    }

  if (FIID_OBJ_GET (obj_cmd_rs, "secondary_rmcp_port_number", &val) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_get: 'secondary_rmcp_port_number': %s\n",
                       fiid_obj_errormsg (obj_cmd_rs));
      goto cleanup;
    }
  secondary_rmcp_port_number = val;

  if (config_section_update_keyvalue_output_unsigned_int (state_data->pstate,
                                                          kv,
                                                          secondary_rmcp_port_number) < 0)
    return (CONFIG_ERR_FATAL_ERROR);

  rv = CONFIG_ERR_SUCCESS;
 cleanup:
  fiid_obj_destroy (obj_cmd_rs);
  return (rv);
}
