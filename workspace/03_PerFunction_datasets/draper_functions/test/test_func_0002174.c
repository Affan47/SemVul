unpack_rsc_colocation(xmlNode * xml_obj, pe_working_set_t * data_set)
{
    int score_i = 0;
    xmlNode *set = NULL;
    xmlNode *last = NULL;
    gboolean any_sets = FALSE;

    xmlNode *orig_xml = NULL;
    xmlNode *expanded_xml = NULL;

    const char *id = crm_element_value(xml_obj, XML_ATTR_ID);
    const char *score = crm_element_value(xml_obj, XML_RULE_ATTR_SCORE);

    gboolean rc = TRUE;

    if (score) {
        score_i = char2score(score);
    }

    rc = unpack_colocation_template(xml_obj, &expanded_xml, data_set);
    if (expanded_xml) {
        orig_xml = xml_obj;
        xml_obj = expanded_xml;

    } else if (rc == FALSE) {
        return FALSE;
    }

    for (set = __xml_first_child(xml_obj); set != NULL; set = __xml_next(set)) {
        if (crm_str_eq((const char *)set->name, XML_CONS_TAG_RSC_SET, TRUE)) {
            any_sets = TRUE;
            set = expand_idref(set, data_set->input);
            if (unpack_colocation_set(set, score_i, data_set) == FALSE) {
                return FALSE;

            } else if (last && colocate_rsc_sets(id, last, set, score_i, data_set) == FALSE) {
                return FALSE;
            }
            last = set;
        }
    }

    if (expanded_xml) {
        free_xml(expanded_xml);
        xml_obj = orig_xml;
    }

    if (any_sets == FALSE) {
        return unpack_simple_colocation(xml_obj, data_set);
    }

    return TRUE;
}
