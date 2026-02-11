hx509_cert_free(hx509_cert cert)
{
    size_t i;

    if (cert == NULL)
	return;

    if (cert->ref <= 0)
	_hx509_abort("cert refcount <= 0 on free");
    if (--cert->ref > 0)
	return;

    if (cert->release)
	(cert->release)(cert, cert->ctx);

    if (cert->private_key)
	hx509_private_key_free(&cert->private_key);

    free_Certificate(cert->data);
    free(cert->data);

    for (i = 0; i < cert->attrs.len; i++) {
	der_free_octet_string(&cert->attrs.val[i]->data);
	der_free_oid(&cert->attrs.val[i]->oid);
	free(cert->attrs.val[i]);
    }
    free(cert->attrs.val);
    free(cert->friendlyname);
    if (cert->basename)
	hx509_name_free(&cert->basename);
    memset(cert, 0, sizeof(*cert));
    free(cert);
}
