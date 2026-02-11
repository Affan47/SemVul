main (int argc, char **argv)
{
        struct Options options;
        enum CRStatus status = CR_OK;

        cr_test_utils_parse_cmd_line (argc, argv, &options);

        if (options.display_help == TRUE) {
                display_help (argv[0]);
                return 0;
        }

        if (options.display_about == TRUE) {
                display_about (argv[0]);
                return 0;
        }

        if (options.files_list == NULL) {
                display_help (argv[0]);
                return 0;
        }

        status = test_cr_parser_parse (options.files_list[0]);

        if (status != CR_OK) {
                fprintf (stdout, "KO\n");
        }

        return 0;
}
