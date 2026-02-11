import_update_entry_subcount(backend *be, ID parentid,
                                        size_t sub_count, int isencrypted)
{
    ldbm_instance *inst = (ldbm_instance *) be->be_instance_info;
    int ret = 0;
    modify_context mc = {0};
    char value_buffer[20];
    struct backentry *e = NULL;
    int isreplace = 0;
    char *numsub_str = numsubordinates;


    e = id2entry(be,parentid,NULL,&ret);
    if ( (NULL == e) || (0 != ret)) {
        ldbm_nasty(sourcefile,5,ret);
        return (0 == ret) ? -1 : ret;
    }


    cache_lock_entry( &inst->inst_cache, e );
    modify_init(&mc,e);
    mc.attr_encrypt = isencrypted;
    sprintf(value_buffer,"%lu",(long unsigned int)sub_count);


    if (slapi_entry_flag_is_set(e->ep_entry, SLAPI_ENTRY_FLAG_TOMBSTONE)) {
        numsub_str = tombstone_numsubordinates;
    }


    isreplace = (attrlist_find(e->ep_entry->e_attrs, numsub_str) != NULL);
    {
        int op = isreplace ? LDAP_MOD_REPLACE : LDAP_MOD_ADD;
        Slapi_Mods *smods= slapi_mods_new();

        slapi_mods_add(smods, op | LDAP_MOD_BVALUES, numsub_str,
                       strlen(value_buffer), value_buffer);
        ret = modify_apply_mods(&mc,smods);
    }
    if (0 == ret || LDAP_TYPE_OR_VALUE_EXISTS == ret) {

        ret = modify_update_all(be,NULL,&mc,NULL);
        if (0 == ret) {
            modify_switch_entries( &mc,be);
        }
    }

    modify_term(&mc,be);
    return ret;
}
