btree_path(btree *root, Object* data, const Comparable_vtable *data_method){
	dlist *head = NULL;
	long c;
	if(root == NULL) return NULL;
	while(root != NULL && (c = data_method->compare(data, root->data)) != 0){
		head = dlist_pushback(head, (Object*)root, FALSE);
		if(c < 0){
			root = root->left;
		} else {
			root = root->right;
		}
	}
	return (root==NULL)?head:dlist_pushback(head, (Object*)root, FALSE);
}
