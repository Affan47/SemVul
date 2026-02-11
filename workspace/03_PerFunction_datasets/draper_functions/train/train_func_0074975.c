zcondition(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    gs_condition_t *pcond =
        ialloc_struct(gs_condition_t, &st_condition, "zcondition");

    if (pcond == 0)
        return_error(e_VMerror);
    pcond->waiting.head_index = pcond->waiting.tail_index = 0;
    push(1);
    make_istruct(op, a_all, pcond);
    return 0;
}
