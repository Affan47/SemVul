_get_authentication_type_support (bmc_config_state_data_t *state_data,
				  const char *section_name)
{
  fiid_obj_t obj_cmd_rs = NULL;
  uint64_t val;
  config_err_t rv = CONFIG_ERR_FATAL_ERROR;
  config_err_t ret;
  uint8_t channel_number;

  assert (state_data);
  assert (section_name);

  if ((ret = get_lan_channel_number (state_data, section_name, &channel_number)) != CONFIG_ERR_SUCCESS)
    {
      rv = ret;
      goto cleanup;
    }

  if (state_data->authentication_type_initialized
      && state_data->authentication_type_channel_number == channel_number)
    goto out;

  state_data->authentication_type_initialized = 0;
  state_data->authentication_type_channel_number = 0;

  if (!(obj_cmd_rs = fiid_obj_create (tmpl_cmd_get_lan_configuration_parameters_authentication_type_support_rs)))
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_create: %s\n",
                       strerror (errno));
      goto cleanup;
    }

  if (ipmi_cmd_get_lan_configuration_parameters_authentication_type_support (state_data->ipmi_ctx,
                                                                             channel_number,
                                                                             IPMI_GET_LAN_PARAMETER,
                                                                             IPMI_LAN_CONFIGURATION_PARAMETERS_NO_SET_SELECTOR,
                                                                             IPMI_LAN_CONFIGURATION_PARAMETERS_NO_BLOCK_SELECTOR,
                                                                             obj_cmd_rs) < 0)
    {
      if (state_data->prog_data->args->config_args.common.debug)
        pstdout_fprintf (state_data->pstate,
                         stderr,
                         "ipmi_cmd_get_lan_configuration_parameters_authentication_type_support: %s\n",
                         ipmi_ctx_errormsg (state_data->ipmi_ctx));

      if (config_is_config_param_non_fatal_error (state_data->ipmi_ctx,
                                                  obj_cmd_rs,
                                                  &ret))
        rv = ret;

      goto cleanup;
    }

  if (FIID_OBJ_GET (obj_cmd_rs, "none", &val) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_get: 'none': %s\n",
                       fiid_obj_errormsg (obj_cmd_rs));
      goto cleanup;
    }
  state_data->authentication_type_none = val;

  if (FIID_OBJ_GET (obj_cmd_rs, "md2", &val) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_get: 'md2': %s\n",
                       fiid_obj_errormsg (obj_cmd_rs));
      goto cleanup;
    }
  state_data->authentication_type_md2 = val;

  if (FIID_OBJ_GET (obj_cmd_rs, "md5", &val) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_get: 'md5': %s\n",
                       fiid_obj_errormsg (obj_cmd_rs));
      goto cleanup;
    }
  state_data->authentication_type_md5 = val;

  if (FIID_OBJ_GET (obj_cmd_rs, "straight_password", &val) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_get: 'straight_password': %s\n",
                       fiid_obj_errormsg (obj_cmd_rs));
      goto cleanup;
    }
  state_data->authentication_type_straight_password = val;

  if (FIID_OBJ_GET (obj_cmd_rs, "oem_proprietary", &val) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_get: 'oem_proprietary': %s\n",
                       fiid_obj_errormsg (obj_cmd_rs));
      goto cleanup;
    }
  state_data->authentication_type_oem_proprietary = val;

  state_data->authentication_type_initialized++;
 out:
  rv = CONFIG_ERR_SUCCESS;
 cleanup:
  fiid_obj_destroy (obj_cmd_rs);
  return (rv);
}
