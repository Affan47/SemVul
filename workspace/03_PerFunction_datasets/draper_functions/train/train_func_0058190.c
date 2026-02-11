krb5_cccol_cursor_next(krb5_context context, krb5_cccol_cursor cursor,
		       krb5_ccache *cache)
{
    krb5_error_code ret;

    *cache = NULL;

    while (cursor->idx < context->num_cc_ops) {

	if (cursor->cursor == NULL) {
	    ret = krb5_cc_cache_get_first (context,
					   context->cc_ops[cursor->idx]->prefix,
					   &cursor->cursor);
	    if (ret) {
		cursor->idx++;
		continue;
	    }
	}
	ret = krb5_cc_cache_next(context, cursor->cursor, cache);
	if (ret == 0)
	    break;

	krb5_cc_cache_end_seq_get(context, cursor->cursor);
	cursor->cursor = NULL;
	if (ret != KRB5_CC_END)
	    break;

	cursor->idx++;
    }
    if (cursor->idx >= context->num_cc_ops) {
	krb5_set_error_message(context, KRB5_CC_END,
			       N_("Reached end of credential caches", ""));
	return KRB5_CC_END;
    }

    return 0;
}
