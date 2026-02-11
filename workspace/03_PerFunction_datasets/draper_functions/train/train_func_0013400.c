_ipmi_raw_args_validate (struct ipmi_raw_arguments *cmd_args)
{
  if ((cmd_args->channel_number
       && !cmd_args->slave_address)
      || (!cmd_args->channel_number
          && cmd_args->slave_address))
    {
      fprintf (stderr, "must specify both channel number and slave address\n");
      exit (1);
    }
}
