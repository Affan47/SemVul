gf_strip_whitespace (char *str, int len)
{
        int     i = 0;
        int     new_len = 0;
        char    *new_str = NULL;

        GF_ASSERT (str);

        new_str = GF_CALLOC (1, len + 1, gf_common_mt_char);
        if (new_str == NULL)
                return -1;

        for (i = 0; i < len; i++) {
                if (!isspace (str[i]))
                        new_str[new_len++] = str[i];
        }
        new_str[new_len] = '\0';

        if (new_len != len) {
                memset (str, 0, len);
                strncpy (str, new_str, new_len);
        }

        GF_FREE (new_str);
        return new_len;
}
