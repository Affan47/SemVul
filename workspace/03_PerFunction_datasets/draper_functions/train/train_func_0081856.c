_set_event_filter_table (struct ipmi_pef_config_state_data *state_data,
                         const char *section_name,
                         struct event_filter_table *eft)
{
  fiid_obj_t obj_cmd_rs = NULL;
  uint8_t filter_number;
  config_err_t rv = CONFIG_ERR_FATAL_ERROR;

  assert (state_data);
  assert (section_name);
  assert (eft);

  filter_number = atoi (section_name + strlen ("Event_Filter_"));

  if (!(obj_cmd_rs = fiid_obj_create (tmpl_cmd_set_pef_configuration_parameters_rs)))
    {
      pstdout_fprintf (state_data->pstate,
                       stderr,
                       "fiid_obj_create: %s\n",
                       strerror (errno));
      goto cleanup;
    }

  if (ipmi_cmd_set_pef_configuration_parameters_event_filter_table (state_data->ipmi_ctx,
                                                                    filter_number,
                                                                    eft->filter_type,
                                                                    eft->enable_filter,
                                                                    eft->event_filter_action_alert,
                                                                    eft->event_filter_action_power_off,
                                                                    eft->event_filter_action_reset,
                                                                    eft->event_filter_action_power_cycle,
                                                                    eft->event_filter_action_oem,
                                                                    eft->event_filter_action_diagnostic_interrupt,
                                                                    eft->event_filter_action_group_control_operation,
                                                                    eft->alert_policy_number,
                                                                    eft->group_control_selector,
                                                                    eft->event_severity,
                                                                    eft->generator_id_byte_1,
                                                                    eft->generator_id_byte_2,
                                                                    eft->sensor_type,
                                                                    eft->sensor_number,
                                                                    eft->event_trigger,
                                                                    eft->event_data1_offset_mask,
                                                                    eft->event_data1_and_mask,
                                                                    eft->event_data1_compare1,
                                                                    eft->event_data1_compare2,
                                                                    eft->event_data2_and_mask,
                                                                    eft->event_data2_compare1,
                                                                    eft->event_data2_compare2,
                                                                    eft->event_data3_and_mask,
                                                                    eft->event_data3_compare1,
                                                                    eft->event_data3_compare2,
                                                                    obj_cmd_rs) < 0)
    {
      config_err_t ret;

      if (state_data->prog_data->args->config_args.common.debug)
        pstdout_fprintf (state_data->pstate,
                         stderr,
                         "ipmi_cmd_set_pef_configuration_parameters_event_filter_table: %s\n",
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
