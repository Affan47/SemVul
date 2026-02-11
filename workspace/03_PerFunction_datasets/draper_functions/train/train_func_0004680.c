push_string(i_ctx_t *i_ctx_p, const char *v)
{   os_ptr op = osp;
    int len = strlen(v);

    push(1);
    make_const_string(op, avm_foreign | a_readonly,
                      len, (const byte *)v);
    return 0;
}
