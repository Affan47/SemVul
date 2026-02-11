removeMin(fnode *n) {
	removeAllFromParent(n->child);
	if(n->right == n) {
		n = n->child;
	} else {

		n->right->left = n->left;
		n->left->right = n->right;
		n = merge(n->right,n->child);
	}

	if(n == NULL)
		return n;


	fnode* trees[64]={NULL};

	while(true) {
		if(trees[n->degree]!=NULL) {
			fnode* t = trees[n->degree];
			if(t == n)
				break;
			trees[n->degree] = NULL;
			if(n->data->key < t->data->key) {
				t->left->right=t->right;
				t->right->left=t->left;
				addChild(n,t);
			} else {
				t->left->right=t->right;
				t->right->left=t->left;
				if(n->right == n) {
					t->right = t->left=t;
					addChild(t,n);
					n = t;
				} else {

					n->left->right=t;
					n->right->left=t;
					t->right=n->right;
					t->left=n->left;
					addChild(t,n);
					n = t;
				}
			}
			trees[n->degree] = n;
			continue;
		} else {
			trees[n->degree] = n;
		}
		n=n->right;
	}
	fnode* min = n;
	fnode *ptr = n;
	do {
		if(ptr->data->key < min->data->key)
			min = ptr;
		ptr = ptr->right;
	} while(ptr != n);
	return min;
}
