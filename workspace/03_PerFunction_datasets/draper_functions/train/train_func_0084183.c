build_options()
{
  unsigned i;
  for(cli_option_count = 0;
      cli_options[cli_option_count].ch || cli_options[cli_option_count].name;
      cli_option_count++) ;
  cli_option_count++;
  cli_full_options = malloc(cli_option_count * sizeof *cli_full_options);
  for(i = 0; i < cli_option_count-1; i++)
    cli_full_options[i] = &cli_options[i];
  cli_full_options[cli_option_count-1] = &cli_help_option;
}
