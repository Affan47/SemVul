check_over_var_entry_semleaf(SemanticLeaf *leaf, int entry)
{
    List *tlist;

    if(leaf->kind == KIND_VAR) {
	if(leaf->entry > entry) {
	    return TRUE;
	}
    } else {
	for(tlist = leaf->subtree; tlist != NULL; tlist = tlist->next) {
	    if(check_over_var_entry_semnode(tlist->data, entry)) {
		return TRUE;
	    }
	}
    }

    return FALSE;
}
