gs_build_function_4(i_ctx_t *i_ctx_p, const ref *op, const gs_function_params_t * mnDR,
                    int depth, gs_function_t ** ppfn, gs_memory_t *mem)
{
    gs_function_PtCr_params_t params;
    ref *proc;
    int code;
    byte *ops;
    int size;

    *(gs_function_params_t *)&params = *mnDR;
    params.ops.data = 0;
    params.ops.size = 0;
    if (dict_find_string(op, "Function", &proc) <= 0) {
        code = gs_note_error(e_rangecheck);
        goto fail;
    }
    if (!r_is_proc(proc)) {
        code = gs_note_error(e_typecheck);
        goto fail;
    }
    size = 0;
    code = check_psc_function(i_ctx_p, proc, 0, NULL, &size);
    if (code < 0)
        goto fail;
    ops = gs_alloc_string(mem, size + 1, "gs_build_function_4(ops)");
    if (ops == 0) {
        code = gs_note_error(e_VMerror);
        goto fail;
    }
    size = 0;
    check_psc_function(i_ctx_p, proc, 0, ops, &size);
    ops[size] = PtCr_return;
    params.ops.data = ops;
    params.ops.size = size + 1;
    code = gs_function_PtCr_init(ppfn, &params, mem);
    if (code >= 0)
        return 0;

fail:
    gs_function_PtCr_free_params(&params, mem);
    return (code < 0 ? code : gs_note_error(e_rangecheck));
}
