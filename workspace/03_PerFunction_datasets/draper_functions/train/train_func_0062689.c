tmap_delete_rebalance(TMap *map, TMapNode *node, TMapNode *parent)
{
    while (node != map->root && !node->red) {
        if (node == parent->left) {
	    TMapNode *sibling = parent->right;
	    if (sibling->red) {
		sibling->red = false;
		parent->red = true;
		tmap_rotate_left(map, parent);
		sibling = parent->right;
            }

            if (!sibling->left->red && !sibling->right->red) {
		sibling->red = true;
		node = parent;
		parent = parent->parent;
            } else {
		if (!sibling->right->red) {
	    	    sibling->left->red = false;
	    	    sibling->red = true;
	    	    tmap_rotate_right(map, sibling);
		    sibling = parent->right;
		}

		sibling->red = parent->red;
		parent->red = false;
		sibling->right->red = false;
		tmap_rotate_left(map, parent);
		node = map->root;
            }
        } else {
            TMapNode *sibling = parent->left;
            if (sibling->red) {
		sibling->red = false;
		parent->red = true;
		tmap_rotate_right(map, parent);
		sibling = parent->left;
            }

            if (!sibling->left->red && !sibling->right->red) {
		sibling->red = true;
		node = parent;
		parent = parent->parent;
            } else {
		if (!sibling->left->red) {
		    sibling->right->red = false;
		    sibling->red = true;
		    tmap_rotate_left(map, sibling);
		    sibling = parent->left;
		}

		sibling->red = parent->red;
		parent->red = false;
		sibling->left->red = false;
		tmap_rotate_right(map, parent);
		node = map->root;
            }
	}
    }

    node->red = false;
}
