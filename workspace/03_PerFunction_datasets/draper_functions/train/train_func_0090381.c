oldLogout()
{
    invalidateLogin(true);

    Transaction trans;
    CKYStatus status = trans.begin(conn);
    if( status != CKYSUCCESS) handleConnectionError();

    selectApplet();

    status = CKYApplet_LogoutAllV0(conn, NULL);
    if (status != CKYSUCCESS) {
	if (status == CKYSCARDERR) {
	    handleConnectionError();
	}
	throw PKCS11Exception(CKR_DEVICE_ERROR);
    }
}
