wasp_tree_lookup( wasp_tree tree, wasp_value key ){
    wasp_key_fn key_fn = tree->key_fn;

    wasp_node node = tree->root;

    while( node ){
        if( node == NULL )return NULL;

        wasp_integer difference = wasp_cmp_eqv( key, key_fn( node->data ) );

        if( difference < 0 ){
            node = node->left;
        }else if( difference > 0 ){
            node = node->right;
        }else{
            break;
        }
    }

    WASP_AUDIT_TREE( tree );

    return node;
}
