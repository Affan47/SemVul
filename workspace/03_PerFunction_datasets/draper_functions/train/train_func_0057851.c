sec_pkcs12_get_nickname_for_cert(sec_PKCS12SafeBag *cert,
				 sec_PKCS12SafeBag *key)
{
    SECItem *nickname;

    if(!cert) {
	PORT_SetError(SEC_ERROR_INVALID_ARGS);
	return NULL;
    }

    nickname = sec_pkcs12_get_nickname(cert);
    if(nickname) {
	return nickname;
    }

    if(key) {
	nickname = sec_pkcs12_get_nickname(key);

        if(nickname && sec_pkcs12_set_nickname(cert, nickname)
			!= SECSuccess) {
	    SECITEM_ZfreeItem(nickname, PR_TRUE);
	    return NULL;
	}
    }

    return nickname;
}
