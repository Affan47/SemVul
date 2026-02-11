hx509_parse_private_key(hx509_context context,
			 const AlgorithmIdentifier *keyai,
			 const void *data,
			 size_t len,
			 hx509_key_format_t format,
			 hx509_private_key *private_key)
{
    struct hx509_private_key_ops *ops;
    int ret;

    *private_key = NULL;

    ops = hx509_find_private_alg(&keyai->algorithm);
    if (ops == NULL) {
	hx509_clear_error_string(context);
	return HX509_SIG_ALG_NO_SUPPORTED;
    }

    ret = hx509_private_key_init(private_key, ops, NULL);
    if (ret) {
	hx509_set_error_string(context, 0, ret, "out of memory");
	return ret;
    }

    ret = (*ops->import)(context, keyai, data, len, format, *private_key);
    if (ret)
	hx509_private_key_free(private_key);

    return ret;
}
