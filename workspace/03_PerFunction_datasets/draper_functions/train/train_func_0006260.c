gkm_assertion_get_attribute (GkmObject *base, GkmSession *session, CK_ATTRIBUTE_PTR attr)
{
	GkmAssertion *self = GKM_ASSERTION (base);

	switch (attr->type)
	{
	case CKA_PRIVATE:
		return gkm_attribute_set_bool (attr, CK_FALSE);
	case CKA_CLASS:
		return gkm_attribute_set_ulong (attr, CKO_X_TRUST_ASSERTION);
	case CKA_MODIFIABLE:
		return gkm_attribute_set_bool (attr, CK_FALSE);


	case CKA_X_ASSERTION_TYPE:
		return gkm_attribute_set_ulong (attr, self->pv->type);
	case CKA_X_PURPOSE:
		return gkm_attribute_set_string (attr, self->pv->purpose);
	case CKA_X_PEER:
		if (!self->pv->peer) {
			gkm_debug ("CKR_ATTRIBUTE_TYPE_INVALID: no CKA_X_PEER on assertion");
			return CKR_ATTRIBUTE_TYPE_INVALID;
		}
		return gkm_attribute_set_string (attr, self->pv->peer);


	case CKA_SERIAL_NUMBER:
	case CKA_ISSUER:
	case CKA_X_CERTIFICATE_VALUE:
		return gkm_object_get_attribute (GKM_OBJECT (self->pv->trust), session, attr);

	default:
		break;
	};

	return GKM_OBJECT_CLASS (gkm_assertion_parent_class)->get_attribute (base, session, attr);
}
