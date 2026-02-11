splay(int64_t *md5, size_t len, struct cache_set *cs) {
    struct node next = {{0, 0}, NULL, NULL, NULL, NULL, NULL, 0, 0}, *right = &next, *left = &next, *temp, *root = cs->root;
    int comp, found = 0;

    if(!root)
	return 0;

    while(1) {
	comp = cmp(md5, len, root->digest, root->size);
	if(comp < 0) {
	    if(!root->left) break;
	    if(cmp(md5, len, root->left->digest, root->left->size) < 0) {
		temp = root->left;
                root->left = temp->right;
		if(temp->right) temp->right->up = root;
                temp->right = root;
		root->up = temp;
                root = temp;
                if(!root->left) break;
	    }
            right->left = root;
	    root->up = right;
            right = root;
            root = root->left;
	} else if(comp > 0) {
	    if(!root->right) break;
	    if(cmp(md5, len, root->right->digest, root->right->size) > 0) {
		temp = root->right;
                root->right = temp->left;
		if(temp->left) temp->left->up = root;
                temp->left = root;
		root->up = temp;
                root = temp;
		if(!root->right) break;
	    }
	    left->right = root;
	    root->up = left;
            left = root;
            root = root->right;
	} else {
	    found = 1;
	    break;
	}
    }

    left->right = root->left;
    if(root->left) root->left->up = left;
    right->left = root->right;
    if(root->right) root->right->up = right;
    root->left = next.right;
    if(next.right) next.right->up = root;
    root->right = next.left;
    if(next.left) next.left->up = root;
    root->up = NULL;
    cs->root = root;
    return found;
}
