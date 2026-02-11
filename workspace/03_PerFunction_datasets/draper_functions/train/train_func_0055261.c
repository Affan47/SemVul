init_cli_options(cli_options_t* options)
{
    int temp_size;

    cli_option_t temp[] =
    {
        OPTION(CLI_OPT_LONI, CLI_LOPT_LONI, CLI_OPT_ARG_LONI, 1, "Set the onion id of the local hidden service.", loni_parse),
        OPTION(CLI_OPT_NICK, CLI_LOPT_NICK, CLI_OPT_ARG_NICK, 1, "Set the nickname for this chat session.", nick_parse),
        OPTION(CLI_OPT_LPRT, CLI_LOPT_LPRT, CLI_OPT_ARG_LPRT, 0, "Set the local listening port.", lprt_parse),
        OPTION(CLI_OPT_RONI, CLI_LOPT_RONI, CLI_OPT_ARG_RONI, 0, "Set the onion id of the remote host to whom a connection should be established.", roni_parse),
        OPTION(CLI_OPT_RPRT, CLI_LOPT_RPRT, CLI_OPT_ARG_RPRT, 0, "Set the remote port of the remote host who will accept connections on this port.", rprt_parse),
        OPTION(CLI_OPT_HELP, CLI_LOPT_HELP, CLI_OPT_ARG_HELP, 0, "Display help.", help_parse)
    };
    temp_size = sizeof(temp) / sizeof(temp[0]);

    if (temp_size > CLI_OPT_AMOUNT)
    {
        return -1;
    }

    memset(options, 0, sizeof(*options));
    memcpy(options->option, &temp, sizeof(temp));
    return 0;
}
