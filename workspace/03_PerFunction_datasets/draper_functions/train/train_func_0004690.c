factory_create_dh_public_key (GkmSession *session, GkmTransaction *transaction,
                              CK_ATTRIBUTE_PTR attrs, CK_ULONG n_attrs)
{
	GkmManager *manager;
	gcry_mpi_t prime = NULL;
	gcry_mpi_t base = NULL;
	gcry_mpi_t value = NULL;
	CK_ATTRIBUTE_PTR idattr;
	GkmObject *object;

	if (!gkm_attributes_find_mpi (attrs, n_attrs, CKA_PRIME, &prime) ||
	    !gkm_attributes_find_mpi (attrs, n_attrs, CKA_BASE, &base) ||
	    !gkm_attributes_find_mpi (attrs, n_attrs, CKA_VALUE, &value)) {
		gcry_mpi_release (prime);
		gcry_mpi_release (base);
		gcry_mpi_release (value);
		gkm_transaction_fail (transaction, CKR_TEMPLATE_INCOMPLETE);
		return NULL;
	}

	manager = gkm_manager_for_template (attrs, n_attrs, session);
	idattr = gkm_attributes_find (attrs, n_attrs, CKA_ID);

	object = GKM_OBJECT (gkm_dh_public_key_new (gkm_session_get_module (session),
	                                            manager, prime, base, value,
	                                            idattr ? g_memdup (idattr->pValue, idattr->ulValueLen) : NULL,
	                                            idattr ? idattr->ulValueLen : 0));
	gkm_attributes_consume (attrs, n_attrs, CKA_PRIME, CKA_BASE, CKA_VALUE, G_MAXULONG);

	gkm_session_complete_object_creation (session, transaction, object,
	                                      TRUE, attrs, n_attrs);
	return object;
}
