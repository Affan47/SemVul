_hx509_private_key_export(hx509_context context,
			  const hx509_private_key key,
			  hx509_key_format_t format,
			  heim_octet_string *data)
{
    if (key->ops->export == NULL) {
	hx509_clear_error_string(context);
	return HX509_UNIMPLEMENTED_OPERATION;
    }
    return (*key->ops->export)(context, key, format, data);
}
