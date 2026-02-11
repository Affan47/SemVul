check_transited(krb5_context context, Ticket *ticket, EncTicketPart *enc)
{
    char **realms;
    unsigned int num_realms, n;
    krb5_error_code ret;


    if(enc->transited.tr_type == 0 && enc->transited.contents.length == 0)
	return 0;

    if(enc->transited.tr_type != DOMAIN_X500_COMPRESS)
	return KRB5KDC_ERR_TRTYPE_NOSUPP;

    if(enc->transited.contents.length == 0)
	return 0;

    ret = krb5_domain_x500_decode(context, enc->transited.contents,
				  &realms, &num_realms,
				  enc->crealm,
				  ticket->realm);
    if(ret)
	return ret;
    ret = krb5_check_transited(context, enc->crealm,
			       ticket->realm,
			       realms, num_realms, NULL);
    for (n = 0; n < num_realms; n++)
	free(realms[n]);
    free(realms);
    return ret;
}
