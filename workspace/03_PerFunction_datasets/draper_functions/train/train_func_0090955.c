cie_set_finish(i_ctx_t *i_ctx_p, gs_color_space * pcs,
               const ref_cie_procs * pcprocs, int edepth, int code)
{
    if (code >= 0)
        code = gs_setcolorspace(igs, pcs);

    rc_decrement_only_cs(pcs, "cie_set_finish");
    if (code < 0) {
        ref_stack_pop_to(&e_stack, edepth);
        return code;
    }
    istate->colorspace[0].procs.cie = *pcprocs;
    pop(1);
    return (ref_stack_count(&e_stack) == edepth ? 0 : o_push_estack);
}
