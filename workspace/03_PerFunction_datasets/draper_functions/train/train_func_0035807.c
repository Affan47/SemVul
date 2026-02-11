valid_ipv6_address (char *address, int length, gf_boolean_t wildcard_acc)
{
        int hex_numbers = 0;
        int value = 0;
        int i = 0;
        char *tmp = NULL, *ptr = NULL, *prev = NULL, *endptr = NULL;
        char ret = 1;
        int is_wildcard = 0;
        int is_compressed = 0;

        tmp = gf_strdup (address);


        if (length <= 0 || tmp[length - 1] == ':') {
                ret = 0;
                goto out;
        }
        for (i = 0; i < (length - 1) ; i++) {
                if (tmp[i] == ':' && tmp[i + 1] == ':') {
                        if (is_compressed == 0)
                                is_compressed = 1;
                        else {
                                ret = 0;
                                goto out;
                        }
                }
        }

        prev = strtok_r (tmp, ":", &ptr);

        while (prev != NULL) {
                hex_numbers++;
                if (wildcard_acc && !strcmp (prev, "*")) {
                        is_wildcard = 1;
                } else {
                        value = strtol (prev, &endptr, 16);
                        if ((value > 0xffff) || (value < 0)
                        || (endptr != NULL && *endptr != '\0')) {
                                ret = 0;
                                goto out;
                        }
                }
                prev = strtok_r (NULL, ":", &ptr);
        }

        if ((hex_numbers > 8) || (hex_numbers < 8 && !is_wildcard
            && !is_compressed)) {
                ret = 0;
        }

out:
        GF_FREE (tmp);
        return ret;
}
