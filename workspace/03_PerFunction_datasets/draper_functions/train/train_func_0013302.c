jl_instantiate_method(jl_function_t *f, jl_tuple_t *sp)
{
    if (f->linfo == NULL)
        return f;
    jl_function_t *nf = jl_new_closure(f->fptr, f->env);
    JL_GC_PUSH(&nf);
    nf->linfo = jl_add_static_parameters(f->linfo, sp);
    JL_GC_POP();
    return nf;
}
