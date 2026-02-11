sftk_handleCertObject(SFTKSession *session,SFTKObject *object)
{
    CK_CERTIFICATE_TYPE type;
    SFTKAttribute *attribute;
    CK_RV crv;


    if ( !sftk_hasAttribute(object,CKA_CERTIFICATE_TYPE) ) {
	return CKR_TEMPLATE_INCOMPLETE;
    }


    if (sftk_isTrue(object,CKA_PRIVATE)) {
	return CKR_ATTRIBUTE_VALUE_INVALID;
    }


    attribute = sftk_FindAttribute(object,CKA_CERTIFICATE_TYPE);
    if (attribute == NULL) return CKR_TEMPLATE_INCOMPLETE;
    type = *(CK_CERTIFICATE_TYPE *)attribute->attrib.pValue;
    sftk_FreeAttribute(attribute);

    if (type != CKC_X_509) {
	return CKR_ATTRIBUTE_VALUE_INVALID;
    }


    if ( !sftk_hasAttribute(object,CKA_VALUE) ) {
	return CKR_TEMPLATE_INCOMPLETE;
    }


    if ( !sftk_hasAttribute(object,CKA_SUBJECT) ) {
	return CKR_TEMPLATE_INCOMPLETE;
    }


    if ( !sftk_hasAttribute(object,CKA_ISSUER) ) {
	return CKR_TEMPLATE_INCOMPLETE;
    }


    if ( !sftk_hasAttribute(object,CKA_SERIAL_NUMBER) ) {
	return CKR_TEMPLATE_INCOMPLETE;
    }


    object->objectInfo = NULL;
    object->infoFree = (SFTKFree) NULL;


    crv = sftk_defaultAttribute(object, CKA_ID, NULL, 0);
    if (crv != CKR_OK) { return crv; }

    if (sftk_isTrue(object,CKA_TOKEN)) {
	SFTKSlot *slot = session->slot;
	SFTKDBHandle *certHandle = sftk_getCertDB(slot);

	if (certHandle == NULL) {
	    return CKR_TOKEN_WRITE_PROTECTED;
	}

	crv = sftkdb_write(certHandle, object, &object->handle);
	sftk_freeDB(certHandle);
	return crv;
    }

    return CKR_OK;
}
