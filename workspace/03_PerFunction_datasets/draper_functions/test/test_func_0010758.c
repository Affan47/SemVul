main (int argc, char **argv)
{
  ipmi_pef_config_prog_data_t prog_data;
  struct ipmi_pef_config_arguments cmd_args;
  int exit_code;
  int hosts_count;
  int rv;

  ipmi_disable_coredump ();

  memset (&prog_data, '\0', sizeof (ipmi_pef_config_prog_data_t));
  prog_data.progname = argv[0];
  ipmi_pef_config_argp_parse (argc, argv, &cmd_args);

  prog_data.args = &cmd_args;

  if ((hosts_count = pstdout_setup (&(prog_data.args->config_args.common.hostname),
                                    prog_data.args->config_args.hostrange.buffer_output,
                                    prog_data.args->config_args.hostrange.consolidate_output,
                                    prog_data.args->config_args.hostrange.fanout,
                                    prog_data.args->config_args.hostrange.eliminate,
                                    prog_data.args->config_args.hostrange.always_prefix)) < 0)
    {
      exit_code = EXIT_FAILURE;
      goto cleanup;
    }

  if (!hosts_count)
    {
      exit_code = EXIT_SUCCESS;
      goto cleanup;
    }

  prog_data.hosts_count = hosts_count;

  if ((rv = pstdout_launch (prog_data.args->config_args.common.hostname,
                            _ipmi_pef_config,
                            &prog_data)) < 0)
    {
      fprintf (stderr,
               "pstdout_launch: %s\n",
               pstdout_strerror (pstdout_errnum));
      exit_code = EXIT_FAILURE;
      goto cleanup;
    }

  exit_code = rv;
 cleanup:
  return (exit_code);
}
