zsetfileposition(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    stream *s;

    check_type(*op, t_integer);
    check_file(s, op - 1);
    if (sseek(s, (gs_offset_t)op->value.intval) < 0)
        return_error(e_ioerror);
    pop(2);
    return 0;
}
