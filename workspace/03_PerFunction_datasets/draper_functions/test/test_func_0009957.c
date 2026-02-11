mep_get_mapped_mods(struct configEntry *config,
    Slapi_Entry *origin, char **mapped_dn)
{
    Slapi_Mods *smods = NULL;
    Slapi_Entry *template = NULL;
    Slapi_Attr *attr = NULL;
    char **vals = NULL;
    char *type = NULL;
    char *value = NULL;
    char *rdn_type = NULL;
    int i = 0;


    if (origin == NULL || config == NULL || config->template_entry == NULL) {
        return NULL;
    } else {
        template = config->template_entry;
    }


    if (slapi_entry_attr_find(config->template_entry, MEP_MAPPED_ATTR_TYPE, &attr) == 0) {
        int numvals = 0;

        slapi_attr_get_numvalues(attr, &numvals);
        smods = slapi_mods_new();
        slapi_mods_init(smods, numvals);
    }


    if ((rdn_type = slapi_entry_attr_get_charptr(template, MEP_RDN_ATTR_TYPE)) == NULL) {
        slapi_log_error( SLAPI_LOG_FATAL, MEP_PLUGIN_SUBSYSTEM,
                "mep_get_mapped_mods: Error getting RDN type from tempate "
                "\"%s\".\n", slapi_sdn_get_dn(config->template_sdn));
        slapi_mods_free(&smods);
        goto bail;
    }


    vals = slapi_entry_attr_get_charray(template, MEP_MAPPED_ATTR_TYPE);
    for (i = 0; vals && vals[i]; ++i) {
        if (mep_parse_mapped_attr(vals[i], origin, &type, &value) == 0) {


            if (slapi_attr_type_cmp(type, rdn_type, SLAPI_TYPE_CMP_EXACT) == 0) {
                if (mapped_dn) {
                    *mapped_dn = slapi_create_dn_string("%s=%s,%s", rdn_type,
                            value, config->managed_base);
                }
            } else {

                slapi_mods_add_string(smods, LDAP_MOD_REPLACE, type, value);
            }
            slapi_ch_free_string(&type);
            slapi_ch_free_string(&value);
        } else {
            slapi_log_error( SLAPI_LOG_FATAL, MEP_PLUGIN_SUBSYSTEM,
                    "mep_get_mapped_mods: Error parsing mapped attribute "
                    "in template \"%s\".\n", slapi_sdn_get_dn(config->template_sdn));
            slapi_mods_free(&smods);
            goto bail;
        }
    }

  bail:
    slapi_ch_free_string(&rdn_type);
    slapi_ch_array_free(vals);

    return smods;
}
