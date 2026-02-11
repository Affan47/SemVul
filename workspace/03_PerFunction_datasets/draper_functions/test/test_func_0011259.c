username_commit (const char *section_name,
                 const struct config_keyvalue *kv,
                 void *arg)
{
  bmc_config_state_data_t *state_data;
  uint8_t userid;
  fiid_obj_t obj_cmd_rs = NULL;
  fiid_obj_t obj_get_user_name_cmd_rs = NULL;
  config_err_t rv = CONFIG_ERR_FATAL_ERROR;

  assert (section_name);
  assert (kv);
  assert (arg);

  state_data = (bmc_config_state_data_t *)arg;
  userid = atoi (section_name + strlen ("User"));


  if (userid == 1)
    {

      if (same (kv->value_input, "NULL")
          || same (kv->value_input, "anonymous"))
        return (CONFIG_ERR_SUCCESS);
      else
        return (CONFIG_ERR_NON_FATAL_ERROR_READ_ONLY);
    }

  if (!(obj_cmd_rs = fiid_obj_create (tmpl_cmd_set_user_name_rs)))
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_create: %s\n",
                       strerror (errno));
      goto cleanup;
    }

  if (ipmi_cmd_set_user_name (state_data->ipmi_ctx,
                              userid,
                              kv->value_input,
                              strlen (kv->value_input),
                              obj_cmd_rs) < 0)
    {
      config_err_t ret;

      if (state_data->prog_data->args->config_args.common.debug)
        pstdout_fprintf (state_data->pstate,
                         stderr,
                         "ipmi_cmd_set_user_name: %s\n",
                         ipmi_ctx_errormsg (state_data->ipmi_ctx));


      if (ipmi_ctx_errnum (state_data->ipmi_ctx) == IPMI_ERR_BAD_COMPLETION_CODE
          && (ipmi_check_completion_code (obj_cmd_rs,
                                          IPMI_COMP_CODE_INVALID_DATA_FIELD_IN_REQUEST) == 1))
        {
	  char username[IPMI_MAX_USER_NAME_LENGTH+1];

	  memset (username, '\0', IPMI_MAX_USER_NAME_LENGTH+1);

	  if (!(obj_get_user_name_cmd_rs = fiid_obj_create (tmpl_cmd_get_user_name_rs)))
	    {
	      pstdout_fprintf (state_data->pstate,
			       stderr,
			       "fiid_obj_create: %s\n",
			       strerror (errno));
	      goto cleanup;
	    }

	  if (ipmi_cmd_get_user_name (state_data->ipmi_ctx,
				      userid,
				      obj_get_user_name_cmd_rs) < 0)
	    {
	      if (state_data->prog_data->args->config_args.common.debug)
		pstdout_fprintf (state_data->pstate,
				 stderr,
				 "ipmi_cmd_get_user_name: %s\n",
				 ipmi_ctx_errormsg (state_data->ipmi_ctx));
	      goto error_out;
	    }

	  if (fiid_obj_get_data (obj_get_user_name_cmd_rs,
				 "user_name",
				 username,
				 IPMI_MAX_USER_NAME_LENGTH) < 0)
	    {
	      pstdout_fprintf (state_data->pstate,
			       stderr,
			       "fiid_obj_get_data: 'user_name': %s\n",
			       fiid_obj_errormsg (obj_get_user_name_cmd_rs));
	      goto cleanup;
	    }

	  if (!strcmp(username, kv->value_input))
	    goto out;
        }

    error_out:
      if (config_is_non_fatal_error (state_data->ipmi_ctx,
                                     obj_cmd_rs,
                                     &ret))
        rv = ret;

      goto cleanup;
    }

 out:
  rv = CONFIG_ERR_SUCCESS;
 cleanup:
  fiid_obj_destroy (obj_cmd_rs);
  fiid_obj_destroy (obj_get_user_name_cmd_rs);
  return (rv);
}
