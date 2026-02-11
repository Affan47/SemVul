C_VerifyInit(CK_SESSION_HANDLE hSession,
	     CK_MECHANISM_PTR pMechanism,
	     CK_OBJECT_HANDLE hKey)
{
    struct session_state *state;
    CK_MECHANISM_TYPE mechs[] = { CKM_RSA_PKCS };
    CK_BBOOL bool_true = CK_TRUE;
    CK_ATTRIBUTE attr[] = {
	{ CKA_VERIFY, &bool_true, sizeof(bool_true) }
    };
    struct st_object *o;
    CK_RV ret;

    INIT_CONTEXT();
    st_logf("VerifyInit\n");
    VERIFY_SESSION_HANDLE(hSession, &state);

    ret = commonInit(attr, sizeof(attr)/sizeof(attr[0]),
		     mechs, sizeof(mechs)/sizeof(mechs[0]),
		     pMechanism, hKey, &o);
    if (ret)
	return ret;

    ret = dup_mechanism(&state->verify_mechanism, pMechanism);
    if (ret == CKR_OK)
	state->verify_object = OBJECT_ID(o);

    return ret;
}
