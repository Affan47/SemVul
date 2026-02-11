cli_cmd_needs_connection (struct cli_cmd_word *word)
{
        if (!strcasecmp ("quit", word->word))
                return 0;

        if (!strcasecmp ("help", word->word))
                return 0;

        if (!strcasecmp ("getwd", word->word))
                return 1;

        if (!strcasecmp ("exit", word->word))
                return 0;

        return CLI_DEFAULT_CONN_TIMEOUT;
}
