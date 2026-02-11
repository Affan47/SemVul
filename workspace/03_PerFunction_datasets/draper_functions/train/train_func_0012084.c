delete_cib_object(xmlNode * parent, xmlNode * delete_spec)
{
    const char *object_name = NULL;
    const char *object_id = NULL;
    xmlNode *equiv_node = NULL;
    int result = pcmk_ok;

    if (delete_spec != NULL) {
        object_name = crm_element_name(delete_spec);
    }
    object_id = crm_element_value(delete_spec, XML_ATTR_ID);

    crm_trace("Processing: <%s id=%s>", crm_str(object_name), crm_str(object_id));

    if (delete_spec == NULL) {
        result = -EINVAL;

    } else if (parent == NULL) {
        result = -EINVAL;

    } else if (object_id == NULL) {

        equiv_node = find_xml_node(parent, object_name, FALSE);

    } else {
        equiv_node = find_entity(parent, object_name, object_id);
    }

    if (result != pcmk_ok) {
        ;

    } else if (equiv_node == NULL) {
        result = pcmk_ok;

    } else if (xml_has_children(delete_spec) == FALSE) {

        crm_debug("Removing leaf: <%s id=%s>", crm_str(object_name), crm_str(object_id));
        free_xml(equiv_node);
        equiv_node = NULL;

    } else {
        xmlNode *child = NULL;

        for (child = __xml_first_child(delete_spec); child != NULL; child = __xml_next(child)) {
            int tmp_result = delete_cib_object(equiv_node, child);


            if (tmp_result != pcmk_ok && result == pcmk_ok) {
                result = tmp_result;
            }
        }
    }

    return result;
}
