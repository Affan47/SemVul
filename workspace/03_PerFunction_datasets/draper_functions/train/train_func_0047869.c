json_to_rcache(krb5_context context, k5_json_value v, krb5_rcache *rcache_out)
{
    krb5_rcache rcache;

    *rcache_out = NULL;
    if (k5_json_get_tid(v) == K5_JSON_TID_NULL)
        return 0;
    if (k5_json_get_tid(v) != K5_JSON_TID_STRING)
        return -1;
    if (krb5_rc_resolve_full(context, &rcache, (char *)k5_json_string_utf8(v)))
        return -1;
    if (krb5_rc_recover_or_initialize(context, rcache, context->clockskew)) {
        krb5_rc_close(context, rcache);
        return -1;
    }
    *rcache_out = rcache;
    return 0;
}
