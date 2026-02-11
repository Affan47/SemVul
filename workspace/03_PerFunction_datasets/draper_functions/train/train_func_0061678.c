valid_host_name (char *address, int length)
{
        int             i = 0;
        int             str_len = 0;
        char            ret = 1;
        char            *dup_addr = NULL;
        char            *temp_str = NULL;
        char            *save_ptr = NULL;

        if ((length > _POSIX_HOST_NAME_MAX) || (length == 1)) {
                ret = 0;
                goto out;
        }

        dup_addr = gf_strdup (address);
        if (!dup_addr) {
                ret = 0;
                goto out;
        }
        temp_str = strtok_r (dup_addr,".", &save_ptr);


        if (!temp_str ||
            !isalnum(temp_str[0]) ||
            !isalnum (temp_str[strlen(temp_str)-1])) {
                ret = 0;
                goto out;
        }
        for (i = 1; i < (strlen (temp_str) - 1); i++) {
                if (!isalnum (temp_str[i]) && (temp_str[i] != '-')) {
                        ret = 0;
                        goto out;
                }
        }


        while ((temp_str = strtok_r (NULL, ".", &save_ptr))) {
                str_len = strlen (temp_str);

                if (!isalpha (temp_str[0]) ||
                    !isalnum (temp_str[str_len-1])) {
                        ret = 0;
                        goto out;
                }
                for (i = 1; i < str_len; i++) {
                        if (!isalnum (temp_str[i]) && (temp_str[i] != '-')) {
                                ret = 0;
                                goto out;
                        }
                }
        }

out:
        if (dup_addr)
                GF_FREE (dup_addr);
        return ret;
}
