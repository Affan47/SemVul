get_short_options(cli_options_t* options)
{
    char* opt_str = malloc(CLI_OPT_AMOUNT * 2 + 1);

    if (opt_str == NULL)
    {
        ui_fatal("Memory allocation for short options failed!");
    }

    opt_str[0] = '\0';

    for (int i = 0; i < CLI_OPT_AMOUNT; i++)
    {

        strncat(opt_str, &options->option[i].opt, 1);


        if (options->option[i].mandatory_argument)
        {
            strncat(opt_str, ":", 1);
        }
    }

    return opt_str;
}
