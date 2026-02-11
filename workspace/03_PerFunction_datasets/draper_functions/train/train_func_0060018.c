handle_read_status(i_ctx_t *i_ctx_p, int ch, const ref * fop,
                   const uint * pindex, op_proc_t cont)
{
    switch (ch) {
        default:
            return copy_error_string(i_ctx_p, fop);
        case EOFC:
            return 1;
        case INTC:
        case CALLC:
            if (pindex) {
                ref index;

                make_int(&index, *pindex);
                return s_handle_read_exception(i_ctx_p, ch, fop, &index, 1,
                                               cont);
            } else
                return s_handle_read_exception(i_ctx_p, ch, fop, NULL, 0,
                                               cont);
    }
}
