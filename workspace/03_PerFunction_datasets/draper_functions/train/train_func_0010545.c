_ipmi_pef_config_config_file_parse (struct ipmi_pef_config_arguments *cmd_args)
{
  struct config_file_data_ipmi_pef_config config_file_data;

  memset (&config_file_data,
          '\0',
          sizeof (struct config_file_data_ipmi_pef_config));

  if (config_file_parse (cmd_args->config_args.common.config_file,
                         0,
                         &(cmd_args->config_args.common),
                         NULL,
                         &(cmd_args->config_args.hostrange),
                         CONFIG_FILE_INBAND | CONFIG_FILE_OUTOFBAND | CONFIG_FILE_HOSTRANGE,
                         CONFIG_FILE_TOOL_IPMI_PEF_CONFIG,
                         &config_file_data) < 0)
    {
      fprintf (stderr, "config_file_parse: %s\n", strerror (errno));
      exit (1);
    }

  if (config_file_data.verbose_count_count)
    cmd_args->config_args.verbose_count = config_file_data.verbose_count;
}
