_get_power_capacity (ipmi_oem_state_data_t *state_data,
		     uint8_t *configuration_parameter_data,
		     unsigned int configuration_parameter_data_len)
{
  fiid_obj_t obj_cmd_rs = NULL;
  int len;
  int rv = -1;

  assert (state_data);


  if (!(obj_cmd_rs = fiid_obj_create (tmpl_cmd_get_system_info_parameters_rs)))
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_create: %s\n",
                       strerror (errno));
      goto cleanup;
    }

  if (ipmi_cmd_get_system_info_parameters (state_data->ipmi_ctx,
                                           IPMI_GET_SYSTEM_INFO_PARAMETER,
                                           IPMI_SYSTEM_INFO_PARAMETER_OEM_DELL_POWER_CAPACITY,
                                           IPMI_SYSTEM_INFO_PARAMETERS_NO_SET_SELECTOR,
                                           IPMI_SYSTEM_INFO_PARAMETERS_NO_BLOCK_SELECTOR,
                                           obj_cmd_rs) < 0)
    {
      if (ipmi_ctx_errnum (state_data->ipmi_ctx) == IPMI_ERR_BAD_COMPLETION_CODE
	  && ((ipmi_check_completion_code (obj_cmd_rs,
					   IPMI_COMP_CODE_GET_SYSTEM_INFO_PARAMETERS_PARAMETER_NOT_SUPPORTED) == 1)
	      || (ipmi_check_completion_code (obj_cmd_rs,
					      IPMI_COMP_CODE_INVALID_DATA_FIELD_IN_REQUEST) == 1)))
	{
	  pstdout_fprintf (state_data->pstate,
			   stderr,
			   "%s:%s option not supported on this system\n",
			   state_data->prog_data->args->oem_id,
			   state_data->prog_data->args->oem_command);
	  goto cleanup;
	}

      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "ipmi_cmd_get_system_info_parameters: %s\n",
                       ipmi_ctx_errormsg (state_data->ipmi_ctx));
      goto cleanup;
    }

  if ((len = fiid_obj_get_data (obj_cmd_rs,
                                "configuration_parameter_data",
                                configuration_parameter_data,
                                configuration_parameter_data_len)) < 0)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_get_data: 'configuration_parameter_data': %s\n",
                       fiid_obj_errormsg (obj_cmd_rs));
      goto cleanup;
    }

  if (len < 12)
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "ipmi_cmd_get_system_info_parameters: invalid buffer length returned: %d\n",
                       len);
      goto cleanup;
    }

  rv = 0;
 cleanup:
  return (rv);
}
