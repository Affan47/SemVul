hx509_ca_tbs_set_template(hx509_context context,
			  hx509_ca_tbs tbs,
			  int flags,
			  hx509_cert cert)
{
    int ret;

    if (flags & HX509_CA_TEMPLATE_SUBJECT) {
	if (tbs->subject)
	    hx509_name_free(&tbs->subject);
	ret = hx509_cert_get_subject(cert, &tbs->subject);
	if (ret) {
	    hx509_set_error_string(context, 0, ret,
				   "Failed to get subject from template");
	    return ret;
	}
    }
    if (flags & HX509_CA_TEMPLATE_SERIAL) {
	der_free_heim_integer(&tbs->serial);
	ret = hx509_cert_get_serialnumber(cert, &tbs->serial);
	tbs->flags.serial = !ret;
	if (ret) {
	    hx509_set_error_string(context, 0, ret,
				   "Failed to copy serial number");
	    return ret;
	}
    }
    if (flags & HX509_CA_TEMPLATE_NOTBEFORE)
	tbs->notBefore = hx509_cert_get_notBefore(cert);
    if (flags & HX509_CA_TEMPLATE_NOTAFTER)
	tbs->notAfter = hx509_cert_get_notAfter(cert);
    if (flags & HX509_CA_TEMPLATE_SPKI) {
	free_SubjectPublicKeyInfo(&tbs->spki);
	ret = hx509_cert_get_SPKI(context, cert, &tbs->spki);
	tbs->flags.key = !ret;
	if (ret)
	    return ret;
    }
    if (flags & HX509_CA_TEMPLATE_KU) {
	KeyUsage ku;
	ret = _hx509_cert_get_keyusage(context, cert, &ku);
	if (ret)
	    return ret;
	tbs->key_usage = KeyUsage2int(ku);
    }
    if (flags & HX509_CA_TEMPLATE_EKU) {
	ExtKeyUsage eku;
	size_t i;
	ret = _hx509_cert_get_eku(context, cert, &eku);
	if (ret)
	    return ret;
	for (i = 0; i < eku.len; i++) {
	    ret = hx509_ca_tbs_add_eku(context, tbs, &eku.val[i]);
	    if (ret) {
		free_ExtKeyUsage(&eku);
		return ret;
	    }
	}
	free_ExtKeyUsage(&eku);
    }
    return 0;
}
