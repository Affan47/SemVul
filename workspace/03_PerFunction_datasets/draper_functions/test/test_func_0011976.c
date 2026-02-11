SECKEY_ConvertToPublicKey(SECKEYPrivateKey *privk)
{
    SECKEYPublicKey *pubk;
    PLArenaPool *arena;
    CERTCertificate *cert;
    SECStatus rv;


    cert = PK11_GetCertFromPrivateKey(privk);
    if (cert) {
	pubk = CERT_ExtractPublicKey(cert);
	CERT_DestroyCertificate(cert);
	return pubk;
    }


    arena = PORT_NewArena (DER_DEFAULT_CHUNKSIZE);
    if (arena == NULL) {
	PORT_SetError (SEC_ERROR_NO_MEMORY);
	return NULL;
    }
    pubk = (SECKEYPublicKey *)PORT_ArenaZAlloc(arena,
						   sizeof (SECKEYPublicKey));
    if (pubk == NULL) {
	PORT_FreeArena(arena,PR_FALSE);
	return NULL;
    }
    pubk->keyType = privk->keyType;
    pubk->pkcs11Slot = NULL;
    pubk->pkcs11ID = CK_INVALID_HANDLE;
    pubk->arena = arena;

    switch(privk->keyType) {
      case nullKey:
      case dhKey:
      case dsaKey:


	break;
      case rsaKey:
	rv = PK11_ReadAttribute(privk->pkcs11Slot,privk->pkcs11ID,
				CKA_MODULUS,arena,&pubk->u.rsa.modulus);
	if (rv != SECSuccess)  break;
	rv = PK11_ReadAttribute(privk->pkcs11Slot,privk->pkcs11ID,
			CKA_PUBLIC_EXPONENT,arena,&pubk->u.rsa.publicExponent);
	if (rv != SECSuccess)  break;
	return pubk;
	break;
    default:
	break;
    }

    PORT_FreeArena (arena, PR_FALSE);
    return NULL;
}
