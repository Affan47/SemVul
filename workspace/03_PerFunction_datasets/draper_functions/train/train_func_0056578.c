get_scalar_list_in_semtree(IntSet dest, SemTree *tree)
{
    if( tree )
	get_scalar_list_in_semnode(dest, tree->root);
}
