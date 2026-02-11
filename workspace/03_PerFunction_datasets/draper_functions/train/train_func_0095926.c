_set_key (bmc_config_state_data_t *state_data,
	  const char *section_name,
          uint8_t key_type,
          const void *key,
          unsigned int key_len)
{
  fiid_obj_t obj_cmd_rs = NULL;
  config_err_t rv = CONFIG_ERR_FATAL_ERROR;
  config_err_t ret;
  uint8_t channel_number;

  assert (state_data);
  assert (section_name);
  assert (key_type == IPMI_CHANNEL_SECURITY_KEYS_KEY_ID_K_R
          || key_type == IPMI_CHANNEL_SECURITY_KEYS_KEY_ID_K_G);
  assert (key);

  if (!(obj_cmd_rs = fiid_obj_create (tmpl_cmd_set_channel_security_keys_rs)))
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

  if (ipmi_cmd_set_channel_security_keys (state_data->ipmi_ctx,
                                          channel_number,
                                          IPMI_CHANNEL_SECURITY_KEYS_OPERATION_SET_KEY,
                                          key_type,
                                          key,
                                          key_len,
                                          obj_cmd_rs) < 0)
    {
      if (state_data->prog_data->args->config_args.common.debug)
        pstdout_fprintf (state_data->pstate,
                         stderr,
                         "ipmi_cmd_set_channel_security_keys: %s\n",
                         ipmi_ctx_errormsg (state_data->ipmi_ctx));
      if (!IPMI_ERRNUM_IS_FATAL_ERROR (state_data->ipmi_ctx))
        rv = CONFIG_ERR_NON_FATAL_ERROR;
      goto cleanup;
    }

  rv = CONFIG_ERR_SUCCESS;
 cleanup:
  fiid_obj_destroy (obj_cmd_rs);
  return (rv);
}
