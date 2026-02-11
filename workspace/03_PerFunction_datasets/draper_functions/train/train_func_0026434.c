hx509_private_key2SPKI(hx509_context context,
			hx509_private_key private_key,
			SubjectPublicKeyInfo *spki)
{
    const struct hx509_private_key_ops *ops = private_key->ops;
    if (ops == NULL || ops->get_spki == NULL) {
	hx509_set_error_string(context, 0, HX509_UNIMPLEMENTED_OPERATION,
			       "Private key have no key2SPKI function");
	return HX509_UNIMPLEMENTED_OPERATION;
    }
    return (*ops->get_spki)(context, private_key, spki);
}
