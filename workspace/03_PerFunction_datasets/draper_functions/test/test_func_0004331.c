test_ruleset(xmlNode * ruleset, GHashTable * node_hash, crm_time_t * now)
{
    gboolean ruleset_default = TRUE;
    xmlNode *rule = NULL;

    for (rule = __xml_first_child(ruleset); rule != NULL; rule = __xml_next(rule)) {
        if (crm_str_eq((const char *)rule->name, XML_TAG_RULE, TRUE)) {
            ruleset_default = FALSE;
            if (test_rule(rule, node_hash, RSC_ROLE_UNKNOWN, now)) {
                return TRUE;
            }
        }
    }

    return ruleset_default;
}
