unpack_domains(xmlNode * xml_domains, pe_working_set_t * data_set)
{
    const char *id = NULL;
    GListPtr domain = NULL;
    xmlNode *xml_node = NULL;
    xmlNode *xml_domain = NULL;

    crm_debug("Unpacking domains");
    data_set->domains =
        g_hash_table_new_full(crm_str_hash, g_str_equal, g_hash_destroy_str,
                              g_hash_destroy_node_list);

    for (xml_domain = __xml_first_child(xml_domains); xml_domain != NULL;
         xml_domain = __xml_next(xml_domain)) {
        if (crm_str_eq((const char *)xml_domain->name, XML_CIB_TAG_DOMAIN, TRUE)) {
            domain = NULL;
            id = crm_element_value(xml_domain, XML_ATTR_ID);

            for (xml_node = __xml_first_child(xml_domain); xml_node != NULL;
                 xml_node = __xml_next(xml_node)) {
                if (crm_str_eq((const char *)xml_node->name, XML_CIB_TAG_NODE, TRUE)) {
                    node_t *copy = NULL;
                    node_t *node = NULL;
                    const char *uname = crm_element_value(xml_node, "name");
                    const char *score = crm_element_value(xml_node, XML_RULE_ATTR_SCORE);

                    if (uname == NULL) {
                        crm_config_err("Invalid domain %s: Must specify id tag in <node>", id);
                        continue;
                    }

                    node = pe_find_node(data_set->nodes, uname);
                    if (node == NULL) {
                        node = pe_find_node_id(data_set->nodes, uname);
                    }
                    if (node == NULL) {
                        crm_config_warn("Invalid domain %s: Node %s does not exist", id, uname);
                        continue;
                    }

                    copy = node_copy(node);
                    copy->weight = char2score(score);
                    crm_debug("Adding %s to domain %s with score %s", node->details->uname, id,
                              score);

                    domain = g_list_prepend(domain, copy);
                }
            }

            if (domain) {
                crm_debug("Created domain %s with %d members", id, g_list_length(domain));
                g_hash_table_replace(data_set->domains, strdup(id), domain);
            }
        }
    }

    return TRUE;
}
