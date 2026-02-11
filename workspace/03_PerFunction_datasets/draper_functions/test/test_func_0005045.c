slapi_matchingrule_is_ordering(const char *oid_or_name, const char *syntax_oid)
{
    struct matchingRuleList *mrl=NULL;

    if (slapi_matchingrule_is_compat(oid_or_name, syntax_oid)) {
        for (mrl = g_get_global_mrl(); mrl != NULL; mrl = mrl->mrl_next) {
            if (mrl->mr_entry->mr_name && !strcasecmp(oid_or_name, mrl->mr_entry->mr_name)) {
                return (mrl->mr_entry->mr_name &&
                        PL_strcasestr(mrl->mr_entry->mr_name, "ordering"));
            }
            if (mrl->mr_entry->mr_oid && !strcmp(oid_or_name, mrl->mr_entry->mr_oid)) {
                return (mrl->mr_entry->mr_name &&
                        PL_strcasestr(mrl->mr_entry->mr_name, "ordering"));
            }
        }
    }

    return 0;
}
