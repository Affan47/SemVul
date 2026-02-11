_ipmi_pet_config_file_parse (struct ipmi_pet_arguments *cmd_args)
{
  struct config_file_data_ipmi_pet config_file_data;

  memset (&config_file_data,
          '\0',
          sizeof (struct config_file_data_ipmi_pet));

  if (config_file_parse (cmd_args->common.config_file,
                         0,
                         &(cmd_args->common),
                         &(cmd_args->sdr),
                         NULL,
                         CONFIG_FILE_INBAND | CONFIG_FILE_OUTOFBAND | CONFIG_FILE_SDR,
                         CONFIG_FILE_TOOL_IPMI_PET,
                         &config_file_data) < 0)
    {
      fprintf (stderr, "config_file_parse: %s\n", strerror (errno));
      exit (1);
    }

  if (config_file_data.verbose_count_count)
    cmd_args->verbose_count = config_file_data.verbose_count;
  if (config_file_data.output_event_severity_count)
    cmd_args->output_event_severity = config_file_data.output_event_severity;
  if (config_file_data.output_event_state_count)
    cmd_args->output_event_state = config_file_data.output_event_state;
  if (config_file_data.event_state_config_file_count)
    cmd_args->event_state_config_file = config_file_data.event_state_config_file;
  if (config_file_data.interpret_oem_data_count)
    cmd_args->interpret_oem_data = config_file_data.interpret_oem_data;
  if (config_file_data.entity_sensor_names_count)
    cmd_args->entity_sensor_names = config_file_data.entity_sensor_names;
  if (config_file_data.no_sensor_type_output_count)
    cmd_args->no_sensor_type_output = config_file_data.no_sensor_type_output;
  if (config_file_data.comma_separated_output_count)
    cmd_args->comma_separated_output = config_file_data.comma_separated_output;
  if (config_file_data.no_header_output_count)
    cmd_args->no_header_output = config_file_data.no_header_output;
  if (config_file_data.non_abbreviated_units_count)
    cmd_args->non_abbreviated_units = config_file_data.non_abbreviated_units;
}
