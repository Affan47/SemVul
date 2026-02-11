_hx509_cert_is_parent_cmp(const Certificate *subject,
			  const Certificate *issuer,
			  int allow_self_signed)
{
    int diff;
    AuthorityKeyIdentifier ai;
    SubjectKeyIdentifier si;
    int ret_ai, ret_si, ret;

    ret = _hx509_name_cmp(&issuer->tbsCertificate.subject,
			  &subject->tbsCertificate.issuer,
			  &diff);
    if (ret)
	return ret;
    if (diff)
	return diff;

    memset(&ai, 0, sizeof(ai));
    memset(&si, 0, sizeof(si));


    ret_ai = find_extension_auth_key_id(subject, &ai);
    if (ret_ai && ret_ai != HX509_EXTENSION_NOT_FOUND)
	return 1;
    ret_si = _hx509_find_extension_subject_key_id(issuer, &si);
    if (ret_si && ret_si != HX509_EXTENSION_NOT_FOUND)
	return -1;

    if (ret_si && ret_ai)
	goto out;
    if (ret_ai)
	goto out;
    if (ret_si) {
	if (allow_self_signed) {
	    diff = 0;
	    goto out;
	} else if (ai.keyIdentifier) {
	    diff = -1;
	    goto out;
	}
    }

    if (ai.keyIdentifier == NULL) {
	Name name;

	if (ai.authorityCertIssuer == NULL)
	    return -1;
	if (ai.authorityCertSerialNumber == NULL)
	    return -1;

	diff = der_heim_integer_cmp(ai.authorityCertSerialNumber,
				    &issuer->tbsCertificate.serialNumber);
	if (diff)
	    return diff;
	if (ai.authorityCertIssuer->len != 1)
	    return -1;
	if (ai.authorityCertIssuer->val[0].element != choice_GeneralName_directoryName)
	    return -1;

	name.element = (enum Name_enum)
	    ai.authorityCertIssuer->val[0].u.directoryName.element;
	name.u.rdnSequence =
	    ai.authorityCertIssuer->val[0].u.directoryName.u.rdnSequence;

	ret = _hx509_name_cmp(&issuer->tbsCertificate.subject,
			      &name,
			      &diff);
	if (ret)
	    return ret;
	if (diff)
	    return diff;
	diff = 0;
    } else
	diff = der_heim_octet_string_cmp(ai.keyIdentifier, &si);
    if (diff)
	goto out;

 out:
    free_AuthorityKeyIdentifier(&ai);
    free_SubjectKeyIdentifier(&si);
    return diff;
}
