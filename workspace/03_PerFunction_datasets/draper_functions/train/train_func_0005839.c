alert_string_commit (const char *section_name,
                     const struct config_keyvalue *kv,
                     void *arg)
{
  ipmi_pef_config_state_data_t *state_data;
  uint8_t string_selector;
  fiid_obj_t obj_cmd_rs = NULL;
  config_err_t rv = CONFIG_ERR_FATAL_ERROR;
  uint8_t *alert_string_buf = NULL;
  unsigned int alert_string_len = 0;
  unsigned int alert_string_buf_len = 0;
  unsigned int blocks;
  unsigned int i;

  assert (section_name);
  assert (kv);
  assert (arg);

  state_data = (ipmi_pef_config_state_data_t *)arg;

  string_selector = atoi (section_name + strlen ("Alert_String_"));

  if (!(obj_cmd_rs = fiid_obj_create (tmpl_cmd_set_pef_configuration_parameters_rs)))
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_create: %s\n",
                       strerror (errno));
      goto cleanup;
    }

  alert_string_len = strlen (kv->value_input);


  alert_string_buf_len = alert_string_len + 1;

  if (!(alert_string_buf = (uint8_t *)malloc (alert_string_buf_len)))
    {
      pstdout_perror (state_data->pstate, "malloc");
      goto cleanup;
    }
  memset (alert_string_buf, '\0', alert_string_buf_len);

  if (alert_string_len)
    memcpy (alert_string_buf, kv->value_input, alert_string_len);

  if (!((alert_string_buf_len) % PEF_ALERT_STRING_BLOCK_SIZE))
    blocks = (alert_string_buf_len)/PEF_ALERT_STRING_BLOCK_SIZE;
  else
    blocks = (alert_string_buf_len)/PEF_ALERT_STRING_BLOCK_SIZE + 1;

  for (i = 0; i < blocks; i++)
    {
      uint8_t len_to_write;

      if ((alert_string_buf_len - (i * PEF_ALERT_STRING_BLOCK_SIZE)) < PEF_ALERT_STRING_BLOCK_SIZE)
        len_to_write = alert_string_buf_len - (i * PEF_ALERT_STRING_BLOCK_SIZE);
      else
        len_to_write = PEF_ALERT_STRING_BLOCK_SIZE;

      if (ipmi_cmd_set_pef_configuration_parameters_alert_strings (state_data->ipmi_ctx,
                                                                   string_selector,
                                                                   i+1,
                                                                   alert_string_buf + (i * PEF_ALERT_STRING_BLOCK_SIZE),
                                                                   len_to_write,
                                                                   obj_cmd_rs) < 0)
        {
          config_err_t ret;

          if (state_data->prog_data->args->config_args.common.debug)
            pstdout_fprintf (state_data->pstate,
                             stderr,
                             "ipmi_cmd_set_pef_configuration_parameters_alert_strings: %s\n",
                             ipmi_ctx_errormsg (state_data->ipmi_ctx));

          if (config_is_config_param_non_fatal_error (state_data->ipmi_ctx,
                                                      obj_cmd_rs,
                                                      &ret))
            rv = ret;

          goto cleanup;
        }
    }

  rv = CONFIG_ERR_SUCCESS;
 cleanup:
  free (alert_string_buf);
  fiid_obj_destroy (obj_cmd_rs);
  return (rv);

}
