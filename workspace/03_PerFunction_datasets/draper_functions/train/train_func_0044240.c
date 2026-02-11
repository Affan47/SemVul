get_lan_channel_number (struct ipmi_pef_config_state_data *state_data,
			const char *section_name,
			uint8_t *channel_number)
{
  config_err_t rv = CONFIG_ERR_FATAL_ERROR;
  config_err_t ret;

  assert (state_data);

  assert (channel_number);


  if (section_name)
    {
      char *ptr;


      if ((ptr = stristr (section_name, "Channel_")))
        {
          (*channel_number) = atoi (ptr + strlen ("Channel_"));
          return (CONFIG_ERR_SUCCESS);
        }
    }


  if (!state_data->prog_data->args->config_args.lan_channel_number_set)
    {
      if (!state_data->lan_channel_numbers_loaded)
        {
          if ((ret = load_lan_channel_numbers (state_data)) != CONFIG_ERR_SUCCESS)
            {
              rv = ret;
              goto cleanup;
            }
        }

      if (!state_data->lan_channel_numbers_count)
        {
          rv = CONFIG_ERR_NON_FATAL_ERROR;
          goto cleanup;
        }

      (*channel_number) = state_data->lan_channel_numbers[0];
    }
  else
    (*channel_number) = state_data->prog_data->args->config_args.lan_channel_number;

  rv = CONFIG_ERR_SUCCESS;
 cleanup:
  return (rv);
}
