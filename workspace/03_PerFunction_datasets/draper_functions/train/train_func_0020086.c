jl_compress_ast(jl_value_t *ast)
{
    ios_t dest;
    jl_ios_mem(&dest, 0);
    int en = jl_gc_is_enabled();
    jl_gc_disable();

    tree_literal_values = jl_alloc_cell_1d(0);
    jl_serialize_value(&dest, ast);


    jl_value_t *v = (jl_value_t*)jl_takebuf_array(&dest);
    if (tree_literal_values->length == 0)
        tree_literal_values = (jl_array_t*)jl_an_empty_cell;
    v = (jl_value_t*)jl_tuple(4, v, tree_literal_values,
                              jl_lam_body((jl_expr_t*)ast)->etype,
                              jl_lam_capt((jl_expr_t*)ast));

    tree_literal_values = NULL;
    if (en)
        jl_gc_enable();
    return v;
}
