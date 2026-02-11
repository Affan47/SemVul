PKCS12_newpass(PKCS12 *p12, char *oldpass, char *newpass)
{


	if(!p12) {
		PKCS12err(PKCS12_F_PKCS12_NEWPASS,PKCS12_R_INVALID_NULL_PKCS12_POINTER);
		return 0;
	}


	if (!PKCS12_verify_mac(p12, oldpass, -1)) {
		PKCS12err(PKCS12_F_PKCS12_NEWPASS,PKCS12_R_MAC_VERIFY_FAILURE);
		return 0;
	}

	if (!newpass_p12(p12, oldpass, newpass)) {
		PKCS12err(PKCS12_F_PKCS12_NEWPASS,PKCS12_R_PARSE_ERROR);
		return 0;
	}

	return 1;
}
