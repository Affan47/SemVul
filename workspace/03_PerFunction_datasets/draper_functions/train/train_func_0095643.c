jl_is_leaf_type(jl_value_t *v)
{
    if (jl_is_tuple(v)) {
        jl_tuple_t *t = (jl_tuple_t*)v;
        size_t i;
        for(i=0; i < t->length; i++) {
            if (!jl_is_leaf_type(jl_tupleref(t, i)))
                return 0;
        }
        return 1;
    }
    if (jl_is_type_type(v) && !jl_has_typevars_(jl_tparam0(v),1))
        return 1;
    if (!jl_is_struct_type(v) && !jl_is_func_type(v) && !jl_is_bits_type(v))
        return 0;
    return !jl_has_typevars_(v,1);
}
