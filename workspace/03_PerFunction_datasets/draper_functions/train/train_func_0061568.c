make_pe_stm_ud(Pe_statement *pe_stm, List *p_list)
{
    if(pe_stm == NULL) {
        return list_copy(p_list);
    }

    return make_statement_ud(pe_stm->stm_head, p_list);
}
