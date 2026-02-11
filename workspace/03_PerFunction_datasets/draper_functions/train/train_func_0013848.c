zcountdictstack(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    uint count = ref_stack_count(&d_stack);

    push(1);
    if (!level2_enabled)
        count--;
    make_int(op, count);
    return 0;
}
