ldbm_instance_add_instance_entry_callback(Slapi_PBlock *pb, Slapi_Entry* entryBefore, Slapi_Entry* entryAfter, int *returncode, char *returntext, void *arg)
{
    char *instance_name;
    struct ldbm_instance *inst= NULL;
    struct ldbminfo *li= (struct ldbminfo *) arg;
    int rc = 0;

    parse_ldbm_instance_entry(entryBefore, &instance_name);


    inst = ldbm_instance_find_by_name(li, instance_name);
    if (inst != NULL) {
        LDAPDebug(LDAP_DEBUG_ANY, "WARNING: ldbm instance %s already exists\n",
                  instance_name, 0, 0);
        if (returntext != NULL)
            PR_snprintf(returntext, SLAPI_DSE_RETURNTEXT_SIZE, "An ldbm instance with the name %s already exists\n",
                    instance_name);
        if (returncode != NULL)
            *returncode = LDAP_UNWILLING_TO_PERFORM;
        slapi_ch_free((void **)&instance_name);
        return SLAPI_DSE_CALLBACK_ERROR;
    }

    if (pb == NULL) {

        rc = ldbm_instance_generate(li, instance_name, NULL);
        if (!rc) {
            inst = ldbm_instance_find_by_name(li, instance_name);
            rc = ldbm_instance_create_default_user_indexes(inst);
        }
    }


    slapi_ch_free((void **)&instance_name);
    return (rc == 0) ? SLAPI_DSE_CALLBACK_OK : SLAPI_DSE_CALLBACK_ERROR;
}
