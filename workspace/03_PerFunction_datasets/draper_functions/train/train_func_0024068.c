zrectclip(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    local_rects_t lr;
    int npop = rect_get(&lr, op, imemory);
    int code;

    if (npop < 0)
        return npop;
    code = gs_rectclip(igs, lr.pr, lr.count);
    rect_release(&lr, imemory);
    if (code < 0)
        return code;
    pop(npop);
    return 0;
}
