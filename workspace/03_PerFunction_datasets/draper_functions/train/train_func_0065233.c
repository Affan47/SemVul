ldbm_instance_index_config_enable_index(ldbm_instance *inst, Slapi_Entry* e)
{
    char *index_name;
    int rc;

    rc=ldbm_index_parse_entry(inst, e, "from DSE add", &index_name);
    if (rc == LDAP_SUCCESS) {

        struct attrinfo *ai = NULL;

        ainfo_get(inst->inst_be, index_name, &ai);
        PR_ASSERT(ai != NULL);
        ai->ai_indexmask &= ~INDEX_OFFLINE;
        slapi_ch_free((void **)&index_name);
    }
    return rc;
}
