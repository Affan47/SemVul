replace_array_leaf(SemanticNode *node, int oldEntry, int newEntry)
{
    SemanticLeaf *leaf;
    List *li;

    switch (node->ldata->kind) {
    case NODE:
	replace_array_leaf(LNODE(node), oldEntry, newEntry);
	break;
    case LEAF:
	leaf = LLEAF(node);
	if (leaf->kind == KIND_ARRAY && leaf->entry == oldEntry) {
	    leaf->entry = newEntry;
	}
	if (leaf->kind == KIND_ARRAY || leaf->kind == KIND_FUNC) {
            for (li = leaf->subtree; li != NULL; li = li->next)
		replace_array_leaf(li->data, oldEntry, newEntry);
	}
	break;
    default:
	break;
    }

    switch (node->rdata->kind) {
    case NODE:
	replace_array_leaf(RNODE(node), oldEntry, newEntry);
	break;
    case LEAF:
	leaf = RLEAF(node);
	if (leaf->kind == KIND_ARRAY && leaf->entry == oldEntry) {
	    leaf->entry = newEntry;
	} else if (leaf->kind == KIND_ARRAY){
            for (li = leaf->subtree; li != NULL; li = li->next)
		replace_array_leaf(li->data, oldEntry, newEntry);
	}
	break;
    default:
	break;
    }
}
