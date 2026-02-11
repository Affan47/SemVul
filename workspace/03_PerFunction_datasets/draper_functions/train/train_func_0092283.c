replace_semtree_for_ud(Boolean array_flag, SemTree *tree, Statement *stm)
{
    List *list = NULL;
    SemTree *stmlist_tree;
    Quadruple *quad;

    if(stm->available_exp != NULL) {
        for(list = stm->available_exp; list->next != NULL; list = list->next);
    }

    for(; list != NULL; list = list->prev) {
	quad = search_quad_for_statementlist(list);
	if(quad->op[0]->kind == KIND_VAR) {
	    stmlist_tree = make_semtree_operand(stm->pe_stm->block->module,
						quad->op[1],
						quad);
	    semtree_replace_scalar(tree, search_entry_for_statementlist(list), stmlist_tree);
	}
	else if(quad->op[0]->kind == KIND_ARRAY && array_flag) {
	    stmlist_tree = make_semtree_operand(stm->pe_stm->block->module,
						quad->op[1],
						quad);
	    semtree_replace_array(tree, quad->op[0]->entry, quad->op[0]->inner->entry, stmlist_tree);
	}
    }
}
