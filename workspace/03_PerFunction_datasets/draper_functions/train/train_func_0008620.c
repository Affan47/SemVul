in_test(i_ctx_t *i_ctx_p, int (*paintproc)(gs_state *))
{
    os_ptr op = osp;
    gx_device hdev;
    int npop = in_path(op, i_ctx_p, &hdev);
    int code;

    if (npop < 0)
        return npop;
    code = (*paintproc)(igs);
    return in_path_result(i_ctx_p, npop, code);
}
