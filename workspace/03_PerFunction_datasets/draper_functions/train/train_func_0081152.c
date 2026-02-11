zexecfunction(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;


    if (!r_is_struct(op) ||
        !r_has_masked_attrs(op, a_executable | a_execute, a_executable | a_all)
        )
        return_error(e_typecheck);
    {
        gs_function_t *pfn = (gs_function_t *) op->value.pstruct;
        int m = pfn->params.m, n = pfn->params.n;
        int diff = n - (m + 1);

        if (diff > 0)
            check_ostack(diff);
        {
            float params[20];
            float *in;
            float *out;
            int code = 0;

            if (m + n <= countof(params)) {
                in = params;
            } else {
                in = (float *)ialloc_byte_array(m + n, sizeof(float),
                                                "%execfunction(in/out)");
                if (in == 0)
                    code = gs_note_error(e_VMerror);
            }
            out = in + m;
            if (code < 0 ||
                (code = float_params(op - 1, m, in)) < 0 ||
                (code = gs_function_evaluate(pfn, in, out)) < 0
                )
                DO_NOTHING;
            else {
                if (diff > 0)
                    push(diff);
                else if (diff < 0) {
                    pop(-diff);
                    op = osp;
                }
                code = make_floats(op + 1 - n, out, n);
            }
            if (in != params)
                ifree_object(in, "%execfunction(in)");
            return code;
        }
    }
}
