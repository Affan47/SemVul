krb5_cc_gen_new(krb5_context context, krb5_ccache *cache)
{
    TRACE_CC_GEN_NEW(context, cache);
    return (*cache)->ops->gen_new(context, cache);
}
