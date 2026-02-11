unpack_template(xmlNode * xml_obj, xmlNode ** expanded_xml, pe_working_set_t * data_set)
{
    xmlNode *cib_resources = NULL;
    xmlNode *template = NULL;
    xmlNode *new_xml = NULL;
    xmlNode *child_xml = NULL;
    xmlNode *rsc_ops = NULL;
    xmlNode *template_ops = NULL;
    const char *template_ref = NULL;
    const char *id = NULL;

    if (xml_obj == NULL) {
        pe_err("No resource object for template unpacking");
        return FALSE;
    }

    template_ref = crm_element_value(xml_obj, XML_CIB_TAG_RSC_TEMPLATE);
    if (template_ref == NULL) {
        return TRUE;
    }

    id = ID(xml_obj);
    if (id == NULL) {
        pe_err("'%s' object must have a id", crm_element_name(xml_obj));
        return FALSE;
    }

    if (crm_str_eq(template_ref, id, TRUE)) {
        pe_err("The resource object '%s' should not reference itself", id);
        return FALSE;
    }

    cib_resources = get_xpath_object("//"XML_CIB_TAG_RESOURCES, data_set->input, LOG_TRACE);
    if (cib_resources == NULL) {
        pe_err("No resources configured");
        return FALSE;
    }

    template = find_entity(cib_resources, XML_CIB_TAG_RSC_TEMPLATE, template_ref);
    if (template == NULL) {
        pe_err("No template named '%s'", template_ref);
        return FALSE;
    }

    new_xml = copy_xml(template);
    xmlNodeSetName(new_xml, xml_obj->name);
    crm_xml_replace(new_xml, XML_ATTR_ID, id);
    template_ops = find_xml_node(new_xml, "operations", FALSE);

    for (child_xml = __xml_first_child(xml_obj); child_xml != NULL;
         child_xml = __xml_next(child_xml)) {
        xmlNode *new_child = NULL;

        new_child = add_node_copy(new_xml, child_xml);

        if (crm_str_eq((const char *)new_child->name, "operations", TRUE)) {
            rsc_ops = new_child;
        }
    }

    if (template_ops && rsc_ops) {
        xmlNode *op = NULL;
        GHashTable *rsc_ops_hash =
            g_hash_table_new_full(crm_str_hash, g_str_equal, g_hash_destroy_str, NULL);

        for (op = __xml_first_child(rsc_ops); op != NULL; op = __xml_next(op)) {
            char *key = template_op_key(op);

            g_hash_table_insert(rsc_ops_hash, key, op);
        }

        for (op = __xml_first_child(template_ops); op != NULL; op = __xml_next(op)) {
            char *key = template_op_key(op);

            if (g_hash_table_lookup(rsc_ops_hash, key) == NULL) {
                add_node_copy(rsc_ops, op);
            }

            free(key);
        }

        if (rsc_ops_hash) {
            g_hash_table_destroy(rsc_ops_hash);
        }

        free_xml(template_ops);
    }


    *expanded_xml = new_xml;


    return TRUE;
}
