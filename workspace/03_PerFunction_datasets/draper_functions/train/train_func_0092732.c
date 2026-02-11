acc_get_cache_next(krb5_context context, krb5_cc_cursor cursor, krb5_ccache *id)
{
    struct cache_iter *iter = cursor;
    cc_ccache_t cache;
    krb5_acc *a;
    krb5_error_code ret;
    int32_t error;

    error = (*iter->iter->func->next)(iter->iter, &cache);
    if (error)
	return translate_cc_error(context, error);

    ret = _krb5_cc_allocate(context, &krb5_acc_ops, id);
    if (ret) {
	(*cache->func->release)(cache);
	return ret;
    }

    ret = acc_alloc(context, id);
    if (ret) {
	(*cache->func->release)(cache);
	free(*id);
	return ret;
    }

    a = ACACHE(*id);
    a->ccache = cache;

    error = get_cc_name(a);
    if (error) {
	acc_close(context, *id);
	*id = NULL;
	return translate_cc_error(context, error);
    }
    return 0;
}
