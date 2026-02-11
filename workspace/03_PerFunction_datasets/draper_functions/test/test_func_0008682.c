cli_cmd_volume_statedump_options_parse (const char **words, int wordcount,
                                        dict_t **options)
{
        int     ret = 0;
        int     i = 0;
        dict_t  *dict = NULL;
        int     option_cnt = 0;
        char    option_str[100] = {0,};

        for (i = 3; i < wordcount; i++, option_cnt++) {
                if (!cli_cmd_validate_dumpoption (words[i])) {
                        ret = -1;
                        goto out;
                }
                strncat (option_str, words[i], sizeof (words [i]));
                strncat (option_str, " ", 1);
        }
        dict = dict_new ();
        if (!dict)
                goto out;

        ret = dict_set_str (dict, "options", gf_strdup (option_str));
        if (ret)
                goto out;

        ret = dict_set_int32 (dict, "option_cnt", option_cnt);
        if (ret)
                goto out;

        *options = dict;
out:
        if (ret && dict)
                dict_destroy (dict);
        if (ret)
                gf_log ("cli", GF_LOG_ERROR, "Error parsing dumpoptions");
        return ret;
}
