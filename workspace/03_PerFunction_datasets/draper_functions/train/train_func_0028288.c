jl_method_lookup(jl_methtable_t *mt, jl_value_t **args, size_t nargs, int cache)
{
    jl_function_t *sf = jl_method_table_assoc_exact(mt, args, nargs);
    if (sf == NULL) {
        jl_tuple_t *tt = arg_type_tuple(args, nargs);
        JL_GC_PUSH(&tt);
        sf = jl_mt_assoc_by_type(mt, tt, cache);
        JL_GC_POP();
    }
    return sf;
}
