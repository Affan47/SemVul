is_primary_credential_p(krb5_context context,
			kcm_ccache ccache,
			krb5_creds *newcred)
{
    krb5_flags whichfields;

    if (ccache->client == NULL)
	return 0;

    if (newcred->client == NULL ||
	!krb5_principal_compare(context, ccache->client, newcred->client))
	return 0;


    if (ccache->creds == NULL)
	return 0;

    whichfields = KRB5_TC_MATCH_KEYTYPE | KRB5_TC_MATCH_FLAGS_EXACT |
		  KRB5_TC_MATCH_TIMES_EXACT | KRB5_TC_MATCH_AUTHDATA |
		  KRB5_TC_MATCH_2ND_TKT | KRB5_TC_MATCH_IS_SKEY;

    return krb5_compare_creds(context, whichfields, newcred, &ccache->creds->cred);
}
