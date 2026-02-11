slapi_get_mapping_tree_node_by_dn(const Slapi_DN *dn)
{
    mapping_tree_node *current_best_match = mapping_tree_root;
    mapping_tree_node *next_best_match = mapping_tree_root;

    if(mapping_tree_freed){

        return NULL;
    }


    if ( sdn_is_nulldn(dn) && mapping_tree_root && mapping_tree_root->mtn_be[0] &&
         mapping_tree_root->mtn_be[0] != slapi_be_select_by_instance_name(DSE_BACKEND)) {
        return( mapping_tree_root );
    }


    while (next_best_match) {
        current_best_match = next_best_match;
        next_best_match = best_matching_child(current_best_match, dn);
    }

    if (current_best_match == mapping_tree_root)
        return NULL;
    else
        return current_best_match;
}
