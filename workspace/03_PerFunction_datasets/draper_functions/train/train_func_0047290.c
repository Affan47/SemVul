avl_find2( Avlnode *root, const void *data, AVL_CMP fcmp )
{
	int	cmp;

	while ( root != 0 && (cmp = (*fcmp)( data, root->avl_data )) != 0 ) {
		cmp = cmp > 0;
		root = root->avl_link[cmp];
	}
	return root;
}
