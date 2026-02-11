CERT_EncodeCRLDistributionPoints (PLArenaPool *arena,
				  CERTCrlDistributionPoints *value,
				  SECItem *derValue)
{
    CRLDistributionPoint **pointList, *point;
    PLArenaPool *ourPool = NULL;
    SECStatus rv = SECSuccess;

    PORT_Assert (derValue);
    PORT_Assert (value && value->distPoints);

    do {
	ourPool = PORT_NewArena (SEC_ASN1_DEFAULT_ARENA_SIZE);
	if (ourPool == NULL) {
	    rv = SECFailure;
	    break;
	}

	pointList = value->distPoints;
	while (*pointList) {
	    point = *pointList;
	    point->derFullName = NULL;
	    point->derDistPoint.data = NULL;

	    switch (point->distPointType) {
	    case generalName:
		point->derFullName = cert_EncodeGeneralNames
		    (ourPool, point->distPoint.fullName);

		if (!point->derFullName ||
		    !SEC_ASN1EncodeItem (ourPool, &point->derDistPoint,
			  point, FullNameTemplate))
		    rv = SECFailure;
		break;

	    case relativeDistinguishedName:
		if (!SEC_ASN1EncodeItem(ourPool, &point->derDistPoint,
		      point, RelativeNameTemplate))
		    rv = SECFailure;
		break;


	    case 0: break;

	    default:
		PORT_SetError (SEC_ERROR_EXTENSION_VALUE_INVALID);
		rv = SECFailure;
		break;
	    }

	    if (rv != SECSuccess)
		break;

	    if (point->reasons.data)
		PrepareBitStringForEncoding (&point->bitsmap, &point->reasons);

	    if (point->crlIssuer) {
		point->derCrlIssuer = cert_EncodeGeneralNames
		    (ourPool, point->crlIssuer);
		if (!point->derCrlIssuer) {
		    rv = SECFailure;
		    break;
	    	}
	    }
	    ++pointList;
	}
	if (rv != SECSuccess)
	    break;
	if (!SEC_ASN1EncodeItem(arena, derValue, value,
		CERTCRLDistributionPointsTemplate)) {
	    rv = SECFailure;
	    break;
	}
    } while (0);
    PORT_FreeArena (ourPool, PR_FALSE);
    return rv;
}
