mtn_internal_be_set_state(Slapi_Backend *be, int state)
{
    mapping_tree_node * node;
    char * be_name;
    int i;
    int change_callback = 0;
    int old_state;

    mtn_wlock();
    be_name = slapi_ch_strdup(slapi_be_get_name(be));
    node = get_mapping_tree_node_by_name(mapping_tree_root, be_name);
    if (node == NULL)
    {
        LDAPDebug(LDAP_DEBUG_TRACE,
            "Warning: backend %s is not declared in mapping tree\n",
             be_name, 0 ,0);
        goto done;
    }


    i = 0;
    while ( (i < node->mtn_be_count) &&
            (node->mtn_backend_names) &&
            (node->mtn_backend_names[i]) &&
            (strcmp(node->mtn_backend_names[i],be_name)))
    {
        i++;
    }

    if  ( (i >= node->mtn_be_count) || (node->mtn_backend_names == NULL) ||
          (node->mtn_backend_names[i] == NULL) )
    {


        LDAPDebug(LDAP_DEBUG_TRACE,
            "Warning: backend %s is not declared in mapping node entry\n",
             be_name, 0 ,0);
        goto done;
    }

    change_callback = 1;
    old_state = node->mtn_be_states[i];


    switch (state)
    {
        case SLAPI_BE_STATE_OFFLINE:
            node->mtn_be[i] = be;
            node->mtn_be_states[i] = SLAPI_BE_STATE_OFFLINE;
        break;

        case SLAPI_BE_STATE_ON:
            node->mtn_be[i] = be;
            node->mtn_be_states[i] = SLAPI_BE_STATE_ON;
        break;

        case SLAPI_BE_STATE_DELETE:
            node->mtn_be[i] = NULL;
            node->mtn_be_states[i] = SLAPI_BE_STATE_DELETE;
        break;
    }

done:
    mtn_unlock();
    if (change_callback)
        mtn_be_state_change(be_name, old_state, state);
    slapi_ch_free( (void **) &be_name);
}
