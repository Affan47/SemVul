make_modinfo_range(Quadruple *qpt, Operand *op,
		  SemTree *node)
{
    Module_table *mpt;
    int dim;

    mpt = qpt->stm->pe_stm->block->module;

    dim = get_dim(semtree_symbol_entry(node), semtree_symbol_kind(node), mpt);

    if(qpt->stm->pe_stm->block->array_info->MayMod == NULL){
	qpt->stm->pe_stm->block->array_info->MayMod
            = make_array_du_semnode(mpt, dim, node);
    }
    else{
	union_operand_to_array_def_use_table_semnode(mpt,
						     qpt->stm->pe_stm->block->array_info->MayMod,
						     op,
						     node);
    }
}
