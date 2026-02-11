attrd_cs_dispatch(cpg_handle_t handle,
                 const struct cpg_name *groupName,
                 uint32_t nodeid, uint32_t pid, void *msg, size_t msg_len)
{
    uint32_t kind = 0;
    xmlNode *xml = NULL;
    const char *from = NULL;
    char *data = pcmk_message_common_cs(handle, nodeid, pid, msg, &kind, &from);

    if(data == NULL) {
        return;
    }
    if (kind == crm_class_cluster) {
        xml = string2xml(data);
        if (xml == NULL) {
            crm_err("Bad message received: '%.120s'", data);
        }
    }

    if (xml != NULL) {
        attr_hash_entry_t *hash_entry = NULL;
        const char *op = crm_element_value(xml, F_ATTRD_TASK);
        const char *host = crm_element_value(xml, F_ATTRD_HOST);
        const char *ignore = crm_element_value(xml, F_ATTRD_IGNORE_LOCALLY);


        crm_xml_add(xml, F_ORIG, from);

        if (host != NULL && safe_str_eq(host, attrd_uname)) {
            crm_notice("Update relayed from %s", from);
            attrd_local_callback(xml);

        } else if (ignore == NULL || safe_str_neq(from, attrd_uname)) {
            crm_trace("%s message from %s", op, from);
            hash_entry = find_hash_entry(xml);
            stop_attrd_timer(hash_entry);
            attrd_perform_update(hash_entry);
        }

        free_xml(xml);
    }

    free(data);
}
