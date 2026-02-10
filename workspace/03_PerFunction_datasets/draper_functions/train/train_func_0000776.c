seckey_ExtractPublicKey(const CERTSubjectPublicKeyInfo *spki)
{
    SECKEYPublicKey *pubk;
    SECItem os, newOs, newParms;
    SECStatus rv;
    PLArenaPool *arena;
    SECOidTag tag;

    arena = PORT_NewArena (DER_DEFAULT_CHUNKSIZE);
    if (arena == NULL)
	return NULL;

    pubk = (SECKEYPublicKey *) PORT_ArenaZAlloc(arena, sizeof(SECKEYPublicKey));
    if (pubk == NULL) {
	PORT_FreeArena (arena, PR_FALSE);
	return NULL;
    }

    pubk->arena = arena;
    pubk->pkcs11Slot = 0;
    pubk->pkcs11ID = CK_INVALID_HANDLE;


    os = spki->subjectPublicKey;
    DER_ConvertBitString (&os);

    tag = SECOID_GetAlgorithmTag(&spki->algorithm);


    rv = SECITEM_CopyItem(arena, &newOs, &os);
    if ( rv == SECSuccess )
    switch ( tag ) {
      case SEC_OID_X500_RSA_ENCRYPTION:
      case SEC_OID_PKCS1_RSA_ENCRYPTION:
	pubk->keyType = rsaKey;
	prepare_rsa_pub_key_for_asn1(pubk);
        rv = SEC_QuickDERDecodeItem(arena, pubk, SECKEY_RSAPublicKeyTemplate, &newOs);
	if (rv == SECSuccess)
	    return pubk;
	break;
      case SEC_OID_ANSIX9_DSA_SIGNATURE:
      case SEC_OID_SDN702_DSA_SIGNATURE:
	pubk->keyType = dsaKey;
	prepare_dsa_pub_key_for_asn1(pubk);
	rv = SEC_QuickDERDecodeItem(arena, pubk, SECKEY_DSAPublicKeyTemplate, &newOs);
	if (rv != SECSuccess) break;

        rv = seckey_DSADecodePQG(arena, pubk,
                                 &spki->algorithm.parameters);

	if (rv == SECSuccess) return pubk;
	break;
      case SEC_OID_X942_DIFFIE_HELMAN_KEY:
	pubk->keyType = dhKey;
	prepare_dh_pub_key_for_asn1(pubk);
	rv = SEC_QuickDERDecodeItem(arena, pubk, SECKEY_DHPublicKeyTemplate, &newOs);
	if (rv != SECSuccess) break;


        rv = SECITEM_CopyItem(arena, &newParms, &spki->algorithm.parameters);
        if ( rv != SECSuccess )
            break;

        rv = SEC_QuickDERDecodeItem(arena, pubk, SECKEY_DHParamKeyTemplate,
                                 &newParms);

	if (rv == SECSuccess) return pubk;
	break;
      case SEC_OID_ANSIX962_EC_PUBLIC_KEY:
	pubk->keyType = ecKey;
	pubk->u.ec.size = 0;


        rv = SECITEM_CopyItem(arena, &pubk->u.ec.DEREncodedParams,
	    &spki->algorithm.parameters);
        if ( rv != SECSuccess )
            break;
        rv = SECITEM_CopyItem(arena, &pubk->u.ec.publicValue, &newOs);
	if (rv == SECSuccess) return pubk;
	break;

      default:
	PORT_SetError(SEC_ERROR_UNSUPPORTED_KEYALG);
	rv = SECFailure;
	break;
    }

    SECKEY_DestroyPublicKey (pubk);
    return NULL;
}
