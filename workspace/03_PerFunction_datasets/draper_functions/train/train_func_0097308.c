cli_cmd_volume_reset_parse (const char **words, int wordcount, dict_t **options)
{
        dict_t  *dict = NULL;
        char    *volname = NULL;
        int     ret = -1;

        GF_ASSERT (words);
        GF_ASSERT (options);

        dict = dict_new ();

        if (!dict)
                goto out;

        if (wordcount < 3)
                goto out;

        if (wordcount > 5)
                goto out;

        volname = (char *)words[2];

        if (!volname) {
                ret = -1;
                goto out;
        }

        ret = dict_set_str (dict, "volname", volname);
        if (ret)
                goto out;

        if (wordcount == 3) {
                ret = dict_set_str (dict, "key", "all");
                if (ret)
                        goto out;
        }

        if (wordcount >= 4) {
                if (!strcmp ("force", (char*)words[3])) {
                        ret = dict_set_int32 (dict, "force", 1);
                        if (ret)
                                goto out;
                        ret = dict_set_str (dict, "key", "all");
                        if (ret)
                                goto out;
                } else {
                        ret = dict_set_str (dict, "key", (char *)words[3]);
                        if (ret)
                                goto out;
                }
        }

        if (wordcount == 5) {
                if (strcmp ("force", (char*)words[4])) {
                        ret = -1;
                        goto out;
                } else {
                        ret = dict_set_int32 (dict, "force", 1);
                        if (ret)
                                goto out;
                }
        }

        *options = dict;

out:
        if (ret && dict) {
                dict_destroy (dict);
        }

                return ret;
}
