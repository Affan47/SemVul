k5_make_realmlist(const char *realm, char ***realms_out)
{
    char **realms;

    *realms_out = NULL;
    realms = calloc(2, sizeof(*realms));
    if (realms == NULL)
        return ENOMEM;
    realms[0] = strdup(realm);
    if (realms[0] == NULL) {
        free(realms);
        return ENOMEM;
    }
    *realms_out = realms;
    return 0;
}
