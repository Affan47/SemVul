cib_process_modify(const char *op, int options, const char *section, xmlNode * req, xmlNode * input,
                   xmlNode * existing_cib, xmlNode ** result_cib, xmlNode ** answer)
{
    xmlNode *obj_root = NULL;

    crm_trace("Processing \"%s\" event", op);

    if (options & cib_xpath) {
        return cib_process_xpath(op, options, section, req, input,
                                 existing_cib, result_cib, answer);
    }

    if (input == NULL) {
        crm_err("Cannot perform modification with no data");
        return -EINVAL;
    }

    obj_root = get_object_root(section, *result_cib);
    if (obj_root == NULL) {
        xmlNode *tmp_section = NULL;
        const char *path = get_object_parent(section);

        if (path == NULL) {
            return -EINVAL;
        }

        tmp_section = create_xml_node(NULL, section);
        cib_process_xpath(CIB_OP_CREATE, 0, path, NULL, tmp_section, NULL, result_cib, answer);
        free_xml(tmp_section);

        obj_root = get_object_root(section, *result_cib);
    }

    CRM_CHECK(obj_root != NULL, return -EINVAL);

    if (update_xml_child(obj_root, input) == FALSE) {
        if (options & cib_can_create) {
            add_node_copy(obj_root, input);
        } else {
            return -ENXIO;
        }
    }

    return pcmk_ok;
}
