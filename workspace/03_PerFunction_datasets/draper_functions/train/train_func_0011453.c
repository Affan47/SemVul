mtn_get_first_node(mapping_tree_node * node, int scope)
{
    if (node == NULL)
        return NULL;


    if (node == mapping_tree_root)
    {
        return node;
    }

    if (scope == LDAP_SCOPE_BASE)
        return node;

    if (scope == LDAP_SCOPE_ONELEVEL)
    {
         if (node->mtn_children)
            return node->mtn_children;
        else
            return node;
    }

    while (node->mtn_children)
        node = node->mtn_children;

    return node;
}
