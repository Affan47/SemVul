gkm_public_xsa_key_create_sexp (GkmSession *session, GkmTransaction *transaction,
                                CK_ATTRIBUTE_PTR attrs, CK_ULONG n_attrs)
{
	CK_KEY_TYPE type;
	gcry_sexp_t sexp;
	CK_RV ret;

	g_return_val_if_fail (GKM_IS_TRANSACTION (transaction), NULL);
	g_return_val_if_fail (attrs || !n_attrs, NULL);

	if (!gkm_attributes_find_ulong (attrs, n_attrs, CKA_KEY_TYPE, &type)) {
		gkm_transaction_fail (transaction, CKR_TEMPLATE_INCOMPLETE);
		return NULL;
	}

	gkm_attributes_consume (attrs, n_attrs, CKA_KEY_TYPE, CKA_CLASS, G_MAXULONG);

	switch (type) {
	case CKK_RSA:
		ret = create_rsa_public (attrs, n_attrs, &sexp);
		break;
	case CKK_DSA:
		ret = create_dsa_public (attrs, n_attrs, &sexp);
		break;
	default:
		ret = CKR_ATTRIBUTE_VALUE_INVALID;
		break;
	};

	if (ret != CKR_OK) {
		gkm_transaction_fail (transaction, ret);
		return NULL;
	}

	g_return_val_if_fail (sexp, NULL);
	return gkm_sexp_new (sexp);
}
