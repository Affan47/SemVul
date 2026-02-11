moddn_rename_child_entry(
    back_txn *ptxn,
    Slapi_PBlock *pb,
    struct ldbminfo *li,
    struct backentry *e,
    struct backentry **ec,
    int parentdncomps,
    char **newsuperiordns,
    int newsuperiordncomps,
    CSN *opcsn)
{


    int retval = 0;
    char *olddn;
    char *newdn;
    char **olddns;
    int olddncomps= 0;
    int need= 1;
    int i;
    int e_in_cache = 1;
    int ec_in_cache = 0;

    olddn = slapi_entry_get_dn((*ec)->ep_entry);
    if (NULL == olddn) {
        return retval;
    }
    olddns = slapi_ldap_explode_dn( olddn, 0 );
    if (NULL == olddns) {
        return retval;
    }
    for(;olddns[olddncomps]!=NULL;olddncomps++);
    for(i=0;i<olddncomps-parentdncomps;i++)
    {
        need+= strlen(olddns[i]) + 2;
    }
    for(i=0;i<newsuperiordncomps;i++)
    {
        need+= strlen(newsuperiordns[i]) + 2;
    }
    need--;
    newdn= slapi_ch_malloc(need);
    newdn[0]= '\0';
    for(i=0;i<olddncomps-parentdncomps;i++)
    {
        strcat(newdn,olddns[i]);
        strcat(newdn,", ");
    }
    for(i=0;i<newsuperiordncomps;i++)
    {
        strcat(newdn,newsuperiordns[i]);
        if(i<newsuperiordncomps-1)
        {

            strcat(newdn,", ");
        }
    }
    slapi_ldap_value_free( olddns );
    slapi_entry_set_dn( (*ec)->ep_entry, newdn );

    add_update_entrydn_operational_attributes (*ec);


    {
        entry_add_dncsn(e->ep_entry, opcsn);
        entry_add_rdn_csn(e->ep_entry, opcsn);
        entry_set_maxcsn(e->ep_entry, opcsn);
    }
    {
        Slapi_Mods smods;
        Slapi_Mods *smodsp = NULL;
        memset(&smods, 0, sizeof(smods));
        slapi_mods_init(&smods, 2);
        slapi_mods_add( &smods, LDAP_MOD_DELETE, LDBM_ENTRYDN_STR,
                    strlen( backentry_get_ndn(e) ), backentry_get_ndn(e) );
        slapi_mods_add( &smods, LDAP_MOD_REPLACE, LDBM_ENTRYDN_STR,
                    strlen( backentry_get_ndn(*ec) ), backentry_get_ndn(*ec) );
        smodsp = &smods;


        retval = modrdn_rename_entry_update_indexes(ptxn, pb, li, e, ec,
                                                    smodsp, NULL, NULL,
                                                    &e_in_cache, &ec_in_cache);

        slapi_mods_done(&smods);
    }
    return retval;
}
