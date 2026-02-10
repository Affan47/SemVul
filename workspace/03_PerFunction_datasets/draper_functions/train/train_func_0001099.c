sec_pkcs12_set_nickname_for_cert(sec_PKCS12SafeBag *cert,
				 sec_PKCS12SafeBag *key,
				 SECItem *nickname)
{
    if(!nickname || !cert) {
	PORT_SetError(SEC_ERROR_INVALID_ARGS);
	return SECFailure;
    }

    if(sec_pkcs12_set_nickname(cert, nickname) != SECSuccess) {
	return SECFailure;
    }

    if(key) {
	if(sec_pkcs12_set_nickname(key, nickname) != SECSuccess) {
	    cert->problem = PR_TRUE;
	    cert->error   = key->error;
	    return SECFailure;
	}
    }

    return SECSuccess;
}
