linked_attrs_mod_backpointers(char *linkdn, char *type,
    char *scope, int modop, Slapi_ValueSet *targetvals)
{
    char *val[2];
    int i = 0;
    Slapi_PBlock *mod_pb = slapi_pblock_new();
    LDAPMod mod;
    LDAPMod *mods[2];
    Slapi_Value *targetval = NULL;


    val[0] = linkdn;
    val[1] = 0;

    mod.mod_op = modop;
    mod.mod_type = type;
    mod.mod_values = val;

    mods[0] = &mod;
    mods[1] = 0;

    i = slapi_valueset_first_value(targetvals, &targetval);
    while(targetval)
    {
        int perform_update = 0;
        const char *targetdn = slapi_value_get_string(targetval);
        Slapi_DN *targetsdn = slapi_sdn_new_dn_byref(targetdn);


        if (scope) {
            perform_update = slapi_dn_issuffix(targetdn, scope);
        } else {
            Slapi_Backend *be = NULL;
            Slapi_DN *linksdn = slapi_sdn_new_normdn_byref(linkdn);

            if ((be = slapi_be_select(linksdn))) {
                perform_update = slapi_sdn_issuffix(targetsdn, slapi_be_getsuffix(be, 0));
            }

            slapi_sdn_free(&linksdn);
        }

        if (perform_update) {
            slapi_log_error(SLAPI_LOG_PLUGIN, LINK_PLUGIN_SUBSYSTEM,
                            "%s backpointer (%s) in entry (%s)\n",
                            (modop == LDAP_MOD_ADD) ? "Adding" : "Removing",
                            linkdn, targetdn);


            slapi_modify_internal_set_pb_ext(mod_pb, targetsdn, mods, 0, 0,
                                             linked_attrs_get_plugin_id(), 0);
            slapi_modify_internal_pb(mod_pb);


            slapi_pblock_init(mod_pb);
        }
        slapi_sdn_free(&targetsdn);

        i = slapi_valueset_next_value(targetvals, i, &targetval);
    }

    slapi_pblock_destroy(mod_pb);
}
