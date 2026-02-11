change_var_operand_in_sem_leaf(SemanticLeaf *leaf, int new_entry, int old_entry)
{
    if(leaf != NULL && leaf->kind == KIND_VAR && leaf->entry == old_entry){
	leaf->entry = new_entry;
    }
}
