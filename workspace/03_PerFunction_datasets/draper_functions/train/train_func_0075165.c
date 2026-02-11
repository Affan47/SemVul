jl_is_const(jl_module_t *m, jl_sym_t *var)
{
    if (m == NULL) m = jl_current_module;
    jl_binding_t *b = jl_get_binding(m, var);
    return b && b->constp;
}
