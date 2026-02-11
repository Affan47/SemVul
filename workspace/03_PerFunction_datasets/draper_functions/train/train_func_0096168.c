expr_list_copy_constructor(expr_list_ty *to, const expr_list_ty *from)
{
    size_t          j;

    trace(("expr_list_copy_constructor(to = %p, from = %p)\n{\n",
            to, from));
    expr_list_constructor(to);
    for (j = 0; j < from->el_nexprs; j++)
        expr_list_append(to, from->el_expr[j]);
    trace(("}\n"));
}
