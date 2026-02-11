parse_sipc_resp(fetion_account *ac, const gchar *body, gint len)
{
    xmlnode *root;
    xmlnode *node;
    gchar   *version;

    g_return_if_fail(ac != NULL);
    g_return_if_fail(body != NULL);
    g_return_if_fail(len != 0);

    root = xmlnode_root(body, len);


    node                = xmlnode_find(root, "client");
    ac->last_login_ip   = xmlnode_prop(root, "last-login-ip");
    ac->public_ip       = xmlnode_prop(root, "public-ip");
    ac->last_login_time = xmlnode_prop(root, "last-login-time");


    node    = xmlnode_find(root, "personal");
    version = xmlnode_prop(node, "version");

    if (g_strcmp0(version, ac->personal_version) == 0) {

        g_free(version);

        xmlnode *personal_root;
        xmlnode *personal_node;

        if (!(personal_root = fetion_config_load_personal(ac))) {
            hybrid_debug_error("fetion", "invalid personal.xml");
            xmlnode_free(root);
            return;
        }

        if (!(personal_node = xmlnode_find(personal_root, "personal"))) {
            hybrid_debug_error("fetion", "invalid personal.xml");
            xmlnode_free(personal_root);
            xmlnode_free(root);
            return;
        }
        get_personal(ac, personal_node);
        xmlnode_free(personal_root);

    } else {

        g_free(ac->personal_version);
        ac->personal_version = version;

        get_personal(ac, node);

        fetion_config_save_personal(ac, node);
    }


    node    = xmlnode_find(root, "contact-list");
    version = xmlnode_prop(node, "version");

    if (g_strcmp0(version, ac->contact_list_version) == 0) {

        g_free(version);

        xmlnode *contact_root;
        xmlnode *contact_node;

        if (!(contact_root = fetion_config_load_buddies(ac))) {
            hybrid_debug_error("fetion", "invalid buddies.xml");
            xmlnode_free(root);
            return;
        }

        if (!(contact_node = xmlnode_find(contact_root, "contact-list"))) {
            hybrid_debug_error("fetion", "invalid buddies.xml");
            xmlnode_free(contact_root);
            xmlnode_free(root);
            return;
        }

        get_contact_list(ac, contact_node);
        xmlnode_free(contact_root);

    } else {


        hybrid_account_clear_buddy(ac->account);


        g_free(ac->contact_list_version);
        ac->contact_list_version = version;

        get_contact_list(ac, node);

        fetion_config_save_buddies(ac, node);
    }


    node = xmlnode_find(root, "custom-config");
    version = xmlnode_prop(node, "version");

    if (g_strcmp0(version, ac->custom_config_version) != 0) {
        g_free(ac->custom_config);
        g_free(ac->custom_config_version);
        ac->custom_config = xmlnode_content(node);
        ac->custom_config_version = version;
    }

    xmlnode_free(root);


    fetion_config_save_account(ac);
}
