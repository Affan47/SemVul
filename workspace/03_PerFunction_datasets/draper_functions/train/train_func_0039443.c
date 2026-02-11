zcleardictstack(i_ctx_t *i_ctx_p)
{
    while (zend(i_ctx_p) >= 0)
        DO_NOTHING;
    return 0;
}
