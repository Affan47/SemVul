group_add_cb(fetion_account *account, const gchar *sipmsg,
            fetion_transaction *trans)
{
    gint code;
    gchar *pos;
    xmlnode *root;
    xmlnode *node;
    gchar *group_name;
    gchar *group_id;

    hybrid_debug_info("fetion", "group add, recv:\n%s", sipmsg);

    if ((code = fetion_sip_get_code(sipmsg)) != 200) {
        goto group_add_error;
    }

    if (!(pos = strstr(sipmsg, "\r\n\r\n"))) {
        goto group_add_error;
    }

    pos += 4;

    if (!(root = xmlnode_root(pos, strlen(pos)))) {
        goto group_add_error;
    }

    if (!(node = xmlnode_find(root, "buddy-list"))) {
        goto group_add_error;
    }

    if (!xmlnode_has_prop(node, "id") || !xmlnode_has_prop(node, "name")) {
        goto group_add_error;
    }

    group_id = xmlnode_prop(node, "id");
    group_name = xmlnode_prop(node, "name");

    hybrid_blist_add_group(account->account, group_id, group_name);

    return HYBRID_OK;

group_add_error:

    hybrid_debug_error("fetion", "group add error: %d", code);


    return HYBRID_ERROR;
}
