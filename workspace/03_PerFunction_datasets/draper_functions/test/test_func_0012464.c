gf_strstr (const char *str, const char *delim, const char *match)
{
        char *tmp      = NULL;
        char *save_ptr = NULL;
        char *tmp_str  = NULL;

        int  ret       = 0;

        tmp_str = strdup (str);

        if (str == NULL || delim == NULL || match == NULL || tmp_str == NULL) {
                gf_log_callingfn (THIS->name, GF_LOG_WARNING, "argument invalid");
                ret = -1;
                goto out;
        }


        tmp = strtok_r (tmp_str, delim, &save_ptr);

        while (tmp) {
                ret = strcmp (tmp, match);

                if (ret == 0)
                        break;

                tmp = strtok_r (NULL, delim, &save_ptr);
        }

out:
        if (tmp_str)
                free (tmp_str);

        return ret;

}
