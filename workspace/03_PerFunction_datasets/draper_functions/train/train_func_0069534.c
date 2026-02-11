set_system_info_common (bmc_device_state_data_t *state_data,
			Bmc_device_system_info_first_set func_cmd_first_set,
			const char *func_cmd_first_set_str,
			Bmc_device_system_info func_cmd,
			const char *func_cmd_str,
			const char *string)
{
  fiid_obj_t obj_cmd_first_set_rs = NULL;
  fiid_obj_t obj_cmd_rs = NULL;
  uint8_t string_length = 0;
  uint8_t string_block_length = 0;
  uint8_t set_selector = 0;
  unsigned int string_count = 0;
  int rv = -1;

  assert (state_data);
  assert (func_cmd_first_set);
  assert (func_cmd_first_set_str);
  assert (func_cmd);
  assert (func_cmd_str);
  assert (state_data);
  assert (string);
  assert (strlen (string) <= IPMI_SYSTEM_INFO_STRING_LEN_MAX);

  if (!(obj_cmd_first_set_rs = fiid_obj_create (tmpl_cmd_set_system_info_parameters_rs)))
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_create: %s\n",
                       strerror (errno));
      goto cleanup;
    }

  if (!(obj_cmd_rs = fiid_obj_create (tmpl_cmd_set_system_info_parameters_rs)))
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_create: %s\n",
                       strerror (errno));
      goto cleanup;
    }

  string_length = strlen (string);
  if (string_length > IPMI_SYSTEM_INFO_FIRST_SET_STRING_LEN_MAX)
    string_block_length = IPMI_SYSTEM_INFO_FIRST_SET_STRING_LEN_MAX;
  else
    string_block_length = string_length;

  if (func_cmd_first_set (state_data->ipmi_ctx,
			  set_selector,
			  IPMI_SYSTEM_INFO_ENCODING_ASCII_LATIN1,
			  string_length,
			  string + string_count,
			  string_block_length,
			  obj_cmd_first_set_rs) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "%s: %s\n",
                       func_cmd_first_set_str,
                       ipmi_ctx_errormsg (state_data->ipmi_ctx));
      goto cleanup;
    }

  string_count += string_block_length;


  set_selector++;
  while (string_count < string_length && set_selector < 17)
    {
      if (fiid_obj_clear (obj_cmd_rs) < 0)
        {
          pstdout_fprintf (state_data->pstate,
                           stderr,
                           "fiid_obj_clear: %s\n",
                           fiid_obj_errormsg (obj_cmd_rs));
          goto cleanup;
        }

      if ((string_length - string_count) > IPMI_SYSTEM_INFO_SET_STRING_LEN_MAX)
	string_block_length = IPMI_SYSTEM_INFO_SET_STRING_LEN_MAX;
      else
	string_block_length = string_length - string_count;

      if (func_cmd (state_data->ipmi_ctx,
                    set_selector,
		    string + string_count,
		    string_block_length,
                    obj_cmd_rs) < 0)
        {
          pstdout_fprintf (state_data->pstate,
                           stderr,
                           "%s: %s\n",
                           func_cmd_str,
                           ipmi_ctx_errormsg (state_data->ipmi_ctx));
          goto cleanup;
        }

      string_count += string_block_length;
      set_selector++;
    }

  rv = 0;
 cleanup:
  fiid_obj_destroy (obj_cmd_first_set_rs);
  fiid_obj_destroy (obj_cmd_rs);
  return (rv);

}
