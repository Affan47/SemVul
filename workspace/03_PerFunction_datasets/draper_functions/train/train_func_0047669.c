glusterd_set_dump_options (char *dumpoptions_path, char *options,
                           int option_cnt)
{
        int     ret = -1;
        char    *dup_options = NULL;
        char    *option = NULL;
        char    *tmpptr = NULL;
        FILE    *fp = NULL;

        if (0 == option_cnt) {
                ret = 0;
                goto out;
        }

        fp = fopen (dumpoptions_path, "w");
        if (!fp) {
                ret = -1;
                goto out;
        }
        dup_options = gf_strdup (options);
        gf_log ("", GF_LOG_INFO, "Recieved following statedump options: %s",
                dup_options);
        option = strtok_r (dup_options, " ", &tmpptr);
        while (option) {
                fprintf (fp, "%s=yes\n", option);
                option = strtok_r (NULL, " ", &tmpptr);
        }

out:
        if (fp)
                fclose (fp);
        return ret;
}
