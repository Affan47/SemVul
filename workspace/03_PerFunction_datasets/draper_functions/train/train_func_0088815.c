mapping_tree_entry_add_callback(Slapi_PBlock *pb, Slapi_Entry* entryBefore, Slapi_Entry* e, int *returncode, char *returntext, void *arg)
{
    mapping_tree_node *node = NULL;
    int i;
    backend * be;


    *returncode = mapping_tree_entry_add(entryBefore, &node);
    if (LDAP_SUCCESS != *returncode || !node)
    {
        return SLAPI_DSE_CALLBACK_ERROR;
    }

    if(node->mtn_parent != NULL && node != mapping_tree_root )
    {


      mapping_tree_node_add_child(node->mtn_parent, node);
    }

    for (i = 0; ((i < node->mtn_be_count) && (node->mtn_backend_names) &&
        (node->mtn_backend_names[i])); i++)
    {
        if ((be = slapi_be_select_by_instance_name(node->mtn_backend_names[i]))
                && (be->be_state == BE_STATE_STARTED))
        {
            mtn_be_state_change(node->mtn_backend_names[i], SLAPI_BE_STATE_DELETE,
                node->mtn_be_states[i]);
        }
    }

    node->mtn_extension = factory_create_extension(mapping_tree_get_extension_type(), node, NULL);


    if (NULL == config_get_default_naming_context()) {
        char *suffix =
                slapi_rdn_get_value(slapi_entry_get_nrdn_const(entryBefore));
        char *escaped = slapi_ch_strdup(suffix);
        if (suffix && escaped) {
            strcpy_unescape_value(escaped, suffix);
        }
        if (escaped) {
            int rc = _mtn_update_config_param(LDAP_MOD_REPLACE,
                                              CONFIG_DEFAULT_NAMING_CONTEXT,
                                              escaped);
            if (rc) {
                LDAPDebug(LDAP_DEBUG_ANY,
                    "mapping_tree_entry_add_callback: "
                    "setting %s to %s failed: RC=%d\n",
                    escaped, CONFIG_DEFAULT_NAMING_CONTEXT, rc);
            }
        }
        slapi_ch_free_string(&suffix);
        slapi_ch_free_string(&escaped);
    }

    return SLAPI_DSE_CALLBACK_OK;
}
