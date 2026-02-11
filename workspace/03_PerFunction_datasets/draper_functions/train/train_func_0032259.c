jar_validate_pkcs7(JAR *jar, JAR_Signer *signer, char *data, long length)
{

    SEC_PKCS7ContentInfo *cinfo = NULL;
    SEC_PKCS7DecoderContext *dcx;
    PRBool goodSig;
    int status = 0;
    SECItem detdig;

    PORT_Assert( jar != NULL && signer != NULL );

    if (jar == NULL || signer == NULL)
	return JAR_ERR_ORDER;

    signer->valid = JAR_ERR_SIG;


    dcx = SEC_PKCS7DecoderStart(jar_catch_bytes, NULL ,
				NULL , jar->mw,
				NULL, NULL, NULL);
    if (dcx == NULL) {

	return JAR_ERR_PK7;
    }

    SEC_PKCS7DecoderUpdate (dcx, data, length);
    cinfo = SEC_PKCS7DecoderFinish (dcx);
    if (cinfo == NULL) {

	return JAR_ERR_PK7;
    }
    if (SEC_PKCS7ContentIsEncrypted (cinfo)) {

	return JAR_ERR_PK7;
    }
    if (SEC_PKCS7ContentIsSigned (cinfo) == PR_FALSE) {

	return JAR_ERR_PK7;
    }

    PORT_SetError(0);


    detdig.len = SHA1_LENGTH;
    detdig.data = signer->digest->sha1;
    goodSig = SEC_PKCS7VerifyDetachedSignature(cinfo,
					       certUsageObjectSigner,
					       &detdig, HASH_AlgSHA1,
					       PR_FALSE);
    jar_gather_signers(jar, signer, cinfo);
    if (goodSig == PR_TRUE) {

	signer->valid = 0;
    } else {
	status = PORT_GetError();
	PORT_Assert( status < 0 );
	if (status >= 0)
	    status = JAR_ERR_SIG;
	jar->valid = status;
	signer->valid = status;
    }
    jar->pkcs7 = PR_TRUE;
    signer->pkcs7 = PR_TRUE;
    SEC_PKCS7DestroyContentInfo(cinfo);
    return status;
}
