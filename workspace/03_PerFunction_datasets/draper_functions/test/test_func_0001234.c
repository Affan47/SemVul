_delete_auth_opt (dict_t *this, char *key, data_t *value, void *data)
{
        char *auth_option_pattern[] = { "auth.addr.*.allow",
                                        "auth.addr.*.reject",
                                        NULL};
        int i = 0;

        for (i = 0; auth_option_pattern[i]; i++) {
                if (fnmatch (auth_option_pattern[i], key, 0) == 0) {
                        dict_del (this, key);
                        break;
                }
        }

        return 0;
}
