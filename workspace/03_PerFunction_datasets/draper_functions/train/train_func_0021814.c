jl_set_global(jl_module_t *m, jl_sym_t *var, jl_value_t *val)
{
    jl_binding_t *bp = jl_get_binding_wr(m, var);
    if (!bp->constp) {
        bp->value = val;
    }
}
