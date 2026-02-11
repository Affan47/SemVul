command_add_list (int argc, char *argv[], ProgEnv *env)
{
    const char *enc_name, *input_name;
    int         opt_idx;
    iconv_t     saved_conv;
    FILE       *input;
    char        line[256];

    enc_name = 0;
    opt_idx = 0;
    saved_conv = env->to_alpha_conv;
    if (strcmp (argv[0], "-e") == 0 ||
        strcmp (argv[0], "--encoding") == 0)
    {
        if (++opt_idx >= argc) {
            fprintf (stderr, "add-list option \"%s\" requires encoding name",
                     argv[0]);
            return opt_idx;
        }
        enc_name = argv[opt_idx++];
    }
    if (opt_idx >= argc) {
        fprintf (stderr, "add-list requires input word list file name\n");
        return opt_idx;
    }
    input_name = argv[opt_idx++];

    if (enc_name) {
        iconv_t conv = iconv_open (ALPHA_ENC, enc_name);
        if ((iconv_t) -1 == conv) {
            fprintf (stderr,
                    "Conversion from \"%s\" to \"%s\" is not supported.\n",
                    enc_name, ALPHA_ENC);
            return opt_idx;
        }

        env->to_alpha_conv = conv;
    }

    input = fopen (input_name, "r");
    if (!input) {
        fprintf (stderr, "add-list: Cannot open input file \"%s\"\n",
                 input_name);
        goto exit_iconv_openned;
    }

    while (fgets (line, sizeof line, input)) {
        char       *key, *data;
        AlphaChar   key_alpha[256];
        TrieData    data_val;

        key = string_trim (line);
        if ('\0' != *key) {

            for (data = key; *data && !strchr ("\t,", *data); ++data)
                ;

            if ('\0' != *data) {
                *data++ = '\0';
                while (isspace (*data))
                    ++data;
            }

            data_val = ('\0' != *data) ? atoi (data) : TRIE_DATA_ERROR;


            conv_to_alpha (env, key, key_alpha, N_ELEMENTS (key_alpha));
            if (!trie_store (env->trie, key_alpha, data_val))
                fprintf (stderr, "Failed to add key '%s' with data %d.\n",
                         key, data_val);
        }
    }

    fclose (input);

exit_iconv_openned:
    if (enc_name) {
        iconv_close (env->to_alpha_conv);
        env->to_alpha_conv = saved_conv;
    }

    return opt_idx;
}
