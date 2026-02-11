jl_gc_add_finalizer(jl_value_t *v, jl_function_t *f)
{
    jl_value_t **bp = (jl_value_t**)ptrhash_bp(&finalizer_table, v);
    if (*bp == HT_NOTFOUND) {
        *bp = (jl_value_t*)f;
    }
    else {
        *bp = (jl_value_t*)jl_tuple2((jl_value_t*)f, *bp);
    }
}
