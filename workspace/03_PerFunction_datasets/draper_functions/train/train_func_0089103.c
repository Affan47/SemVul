NSS_CMSGenericWrapperData_Encode_AfterData(SECOidTag type,
				    NSSCMSGenericWrapperData *gd)
{
    const nsscmstypeInfo *typeInfo;


    if (type == SEC_OID_PKCS7_DATA) {
	return SECSuccess;
    }

    typeInfo = nss_cmstype_lookup(type);
    if (typeInfo) {
	if  (typeInfo->encode_after) {
	    return (*typeInfo->encode_after)(gd);
	}

	if (typeInfo->isData) {
	    return SECSuccess;
	}
    }

    return SECFailure;
}
