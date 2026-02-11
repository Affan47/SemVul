expr_list_code_generate(const expr_list_ty *elp, opcode_list_ty *olp)
{
    size_t          j;

    for (j = 0; j < elp->el_nexprs; ++j)
        expr_code_generate(elp->el_expr[j], olp);
}
