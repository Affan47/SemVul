_set_sol_sol_authentication (bmc_config_state_data_t *state_data,
			     const char *section_name,
                             struct sol_authentication *sa)
{
  fiid_obj_t obj_cmd_rs = NULL;
  config_err_t rv = CONFIG_ERR_FATAL_ERROR;
  config_err_t ret;
  uint8_t channel_number;

  assert (state_data);
  assert (section_name);
  assert (sa);

  if (!(obj_cmd_rs = fiid_obj_create (tmpl_cmd_set_sol_configuration_parameters_rs)))
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_create: %s\n",
                       strerror (errno));
      goto cleanup;
    }

  if ((ret = get_sol_channel_number (state_data, section_name, &channel_number)) != CONFIG_ERR_SUCCESS)
    {
      rv = ret;
      goto cleanup;
    }

  if (ipmi_cmd_set_sol_configuration_parameters_sol_authentication (state_data->ipmi_ctx,
                                                                    channel_number,
                                                                    sa->sol_privilege_level,
                                                                    sa->force_sol_payload_authentication,
                                                                    sa->force_sol_payload_encryption,
                                                                    obj_cmd_rs) < 0)
    {
      if (state_data->prog_data->args->config_args.common.debug)
        pstdout_fprintf (state_data->pstate,
                         stderr,
                         "ipmi_cmd_set_sol_configuration_parameters_sol_authentication: %s\n",
                         ipmi_ctx_errormsg (state_data->ipmi_ctx));

      if (config_is_config_param_non_fatal_error (state_data->ipmi_ctx,
                                                  obj_cmd_rs,
                                                  &ret))
        rv = ret;

      goto cleanup;
    }

  rv = CONFIG_ERR_SUCCESS;
 cleanup:
  fiid_obj_destroy (obj_cmd_rs);
  return (rv);
}
