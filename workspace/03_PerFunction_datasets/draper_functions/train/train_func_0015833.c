validate_list_elements (const char *string, volume_option_t *opt,
                        int (key_validator)( const char *),
                        int (value_validator)( const char *, volume_option_t *))
{

        char                    *dup_string = NULL;
        char                    *str_sav = NULL;
        char                    *substr_sav = NULL;
        char                    *str_ptr = NULL;
        char                    *key = NULL;
        char                    *value = NULL;
        int                     ret = 0;

        GF_ASSERT (string);

        dup_string = gf_strdup (string);
        if (NULL == dup_string)
                goto out;

        str_ptr = strtok_r (dup_string, ",", &str_sav);
        if (str_ptr == NULL) {
                ret = -1;
                goto out;
        }
        while (str_ptr) {

                key = strtok_r (str_ptr, ":", &substr_sav);
                if (!key ||
                    (key_validator && key_validator(key))) {
                        ret = -1;
                        gf_log (THIS->name, GF_LOG_WARNING,
                                "invalid list '%s', key '%s' not valid.",
                                string, key);
                        goto out;
                }

                value = strtok_r (NULL, ":", &substr_sav);
                if (!value ||
                    (value_validator && value_validator(value, opt))) {
                        ret = -1;
                        gf_log (THIS->name, GF_LOG_WARNING,
                                "invalid list '%s', value '%s' not valid.",
                                string, key);
                        goto out;
                }

                str_ptr = strtok_r (NULL, ",", &str_sav);
                substr_sav = NULL;
        }

 out:
        GF_FREE (dup_string);
        gf_log (THIS->name, GF_LOG_DEBUG, "Returning %d", ret);
        return ret;
}
