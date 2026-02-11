generate_configuration_body(fetion_account *ac)
{
    xmlnode *root;
    xmlnode *node;
    gchar root_node[] = "<config></config>";
    gchar   *res;

    g_return_val_if_fail(ac != NULL, NULL);

    root = xmlnode_root(root_node, strlen(root_node));

    node = xmlnode_new_child(root, "user");

    if (ac->mobileno && *(ac->mobileno) != '\0') {
        xmlnode_new_prop(node, "mobile-no", ac->mobileno);

    } else {
        xmlnode_new_prop(node, "sid", ac->sid);
    }

    node = xmlnode_new_child(root, "client");
    xmlnode_new_prop(node, "type", "HYBRID");
    xmlnode_new_prop(node, "version", PROTO_VERSION);
    xmlnode_new_prop(node, "platform", "W5.1");

    node = xmlnode_new_child(root, "servers");
    xmlnode_new_prop(node, "version", ac->cfg_server_version);

    node = xmlnode_new_child(root, "parameters");
    xmlnode_new_prop(node, "version", ac->cfg_param_version);

    node = xmlnode_new_child(root, "hints");
    xmlnode_new_prop(node, "version", ac->cfg_hint_version);

    res = xmlnode_to_string(root);

    xmlnode_free(root);

    return res;
}
