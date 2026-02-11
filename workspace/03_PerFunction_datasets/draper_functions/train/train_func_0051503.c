run_cmd_args (bmc_info_state_data_t *state_data)
{
  struct bmc_info_arguments *args;
  int rv = -1;

  assert (state_data);

  args = state_data->prog_data->args;

  if (args->get_device_id)
    return (display_get_device_id (state_data));

  if (args->get_device_guid)
    return (display_get_device_guid (state_data));

  if (args->get_system_info)
    return (display_system_info (state_data));

  if (args->get_channel_info)
    return (display_channel_info (state_data));


  if (display_get_device_id (state_data) < 0)
    goto cleanup;

  if (display_get_device_guid (state_data) < 0)
    goto cleanup;

  if (display_system_info (state_data) < 0)
    goto cleanup;

  if (display_channel_info (state_data) < 0)
    goto cleanup;

  rv = 0;
 cleanup:
  return (rv);
}
