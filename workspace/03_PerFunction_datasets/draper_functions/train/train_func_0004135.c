zcachestatus(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    uint status[7];

    gs_cachestatus(ifont_dir, status);
    push(7);
    make_uint_array(op - 6, status, 7);
    return 0;
}
