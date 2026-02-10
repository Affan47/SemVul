hx509_ca_sign(hx509_context context,
	      hx509_ca_tbs tbs,
	      hx509_cert signer,
	      hx509_cert *certificate)
{
    const Certificate *signer_cert;
    AuthorityKeyIdentifier ai;
    int ret;

    memset(&ai, 0, sizeof(ai));

    signer_cert = _hx509_get_cert(signer);

    ret = get_AuthorityKeyIdentifier(context, signer_cert, &ai);
    if (ret)
	goto out;

    ret = ca_sign(context,
		  tbs,
		  _hx509_cert_private_key(signer),
		  &ai,
		  &signer_cert->tbsCertificate.subject,
		  certificate);

out:
    free_AuthorityKeyIdentifier(&ai);

    return ret;
}
