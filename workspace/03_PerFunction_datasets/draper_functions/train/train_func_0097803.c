parse_command_line (int a_argc, char **a_argv, struct Options *a_options)
{
        int i = 0;

        g_return_if_fail (a_options);

        memset (a_options, 0, sizeof (struct Options));

        for (i = 1; i < a_argc; i++) {
                if (a_argv[i][0] != '-')
                        break;

                if (!strcmp (a_argv[i], "-h")
                    || !strcmp (a_argv[i], "--help")) {
                        a_options->display_help = TRUE;
                }
                if (!strcmp (a_argv[i], "--about")) {
                        a_options->display_about = TRUE;
                }
        }

        if (i >= a_argc) {

                a_options->files_list = NULL;
        } else {
                a_options->files_list = &a_argv[i];
        }
}
