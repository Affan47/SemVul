PK11_GetCertFromPrivateKey(SECKEYPrivateKey *privKey)
{
    PK11SlotInfo *slot = privKey->pkcs11Slot;
    CK_OBJECT_HANDLE handle = privKey->pkcs11ID;
    CK_OBJECT_HANDLE certID =
		PK11_MatchItem(slot,handle,CKO_CERTIFICATE);
    CERTCertificate *cert;

    if (certID == CK_INVALID_HANDLE) {
	PORT_SetError(SSL_ERROR_NO_CERTIFICATE);
	return NULL;
    }
    cert = PK11_MakeCertFromHandle(slot,certID,NULL);
    return (cert);

}
