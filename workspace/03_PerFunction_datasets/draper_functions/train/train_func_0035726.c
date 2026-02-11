search_same_quadruple(Statement *stm, SemTree *subtree)
{
    Statement *spt;
    Quadruple *qpt, *ppt;
    Module_table *module = stm->pe_stm->block->module;
    SemTree *tmptree;
    int cmp;

    for (spt = stm->prev; spt != NULL; spt = spt->prev) {
        if (spt->ope == OPE_ASSIGN) {
            qpt = stm_search_assign_qr(spt);
            for (ppt = qpt->prev; ppt != NULL; ppt = ppt->prev) {
                if (ppt->op[0]->kind == qpt->op[1]->kind
                    && ppt->op[0]->entry == qpt->op[1]->entry) {
                    tmptree = make_semtree_operand(module, ppt->op[0], ppt);
                    cmp = compare_semtree(tmptree, subtree);

                    semtree_destruct(tmptree);
                    if (cmp == 0) {
                        return qpt;
                    }
                }
            }
        }
    }

    return NULL;
}
