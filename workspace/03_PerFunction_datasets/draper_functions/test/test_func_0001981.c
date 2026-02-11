SECKEY_ECParamsToBasePointOrderLen(const SECItem *encodedParams)
{
    SECOidTag tag;
    SECItem oid = { siBuffer, NULL, 0};


    oid.len = encodedParams->data[1];
    oid.data = encodedParams->data + 2;
    if ((tag = SECOID_FindOIDTag(&oid)) == SEC_OID_UNKNOWN)
	return 0;

    switch (tag) {
    case SEC_OID_SECG_EC_SECP112R1:
        return 112;
    case SEC_OID_SECG_EC_SECP112R2:
        return 110;

    case SEC_OID_SECG_EC_SECT113R1:
    case SEC_OID_SECG_EC_SECT113R2:
	return 113;

    case SEC_OID_SECG_EC_SECP128R1:
	return 128;
    case SEC_OID_SECG_EC_SECP128R2:
	return 126;

    case SEC_OID_SECG_EC_SECT131R1:
    case SEC_OID_SECG_EC_SECT131R2:
	return 131;

    case SEC_OID_SECG_EC_SECP160K1:
    case SEC_OID_SECG_EC_SECP160R1:
    case SEC_OID_SECG_EC_SECP160R2:
	return 161;

    case SEC_OID_SECG_EC_SECT163K1:
	return 163;
    case SEC_OID_SECG_EC_SECT163R1:
	return 162;
    case SEC_OID_SECG_EC_SECT163R2:
    case SEC_OID_ANSIX962_EC_C2PNB163V1:
	return 163;
    case SEC_OID_ANSIX962_EC_C2PNB163V2:
    case SEC_OID_ANSIX962_EC_C2PNB163V3:
	return 162;

    case SEC_OID_ANSIX962_EC_C2PNB176V1:
	return 161;

    case SEC_OID_ANSIX962_EC_C2TNB191V1:
	return 191;
    case SEC_OID_ANSIX962_EC_C2TNB191V2:
	return 190;
    case SEC_OID_ANSIX962_EC_C2TNB191V3:
	return 189;
    case SEC_OID_ANSIX962_EC_C2ONB191V4:
	return 191;
    case SEC_OID_ANSIX962_EC_C2ONB191V5:
	return 188;

    case SEC_OID_SECG_EC_SECP192K1:
    case SEC_OID_ANSIX962_EC_PRIME192V1:
    case SEC_OID_ANSIX962_EC_PRIME192V2:
    case SEC_OID_ANSIX962_EC_PRIME192V3:
	return 192;

    case SEC_OID_SECG_EC_SECT193R1:
    case SEC_OID_SECG_EC_SECT193R2:
	return 193;

    case SEC_OID_ANSIX962_EC_C2PNB208W1:
	return 193;

    case SEC_OID_SECG_EC_SECP224K1:
	return 225;
    case SEC_OID_SECG_EC_SECP224R1:
	return 224;

    case SEC_OID_SECG_EC_SECT233K1:
	return 232;
    case SEC_OID_SECG_EC_SECT233R1:
	return 233;

    case SEC_OID_SECG_EC_SECT239K1:
    case SEC_OID_ANSIX962_EC_C2TNB239V1:
	return 238;
    case SEC_OID_ANSIX962_EC_C2TNB239V2:
	return 237;
    case SEC_OID_ANSIX962_EC_C2TNB239V3:
	return 236;
    case SEC_OID_ANSIX962_EC_C2ONB239V4:
	return 238;
    case SEC_OID_ANSIX962_EC_C2ONB239V5:
	return 237;
    case SEC_OID_ANSIX962_EC_PRIME239V1:
    case SEC_OID_ANSIX962_EC_PRIME239V2:
    case SEC_OID_ANSIX962_EC_PRIME239V3:
	return 239;

    case SEC_OID_SECG_EC_SECP256K1:
    case SEC_OID_ANSIX962_EC_PRIME256V1:
	return 256;

    case SEC_OID_ANSIX962_EC_C2PNB272W1:
	return 257;

    case SEC_OID_SECG_EC_SECT283K1:
	return 281;
    case SEC_OID_SECG_EC_SECT283R1:
	return 282;

    case SEC_OID_ANSIX962_EC_C2PNB304W1:
	return 289;

    case SEC_OID_ANSIX962_EC_C2TNB359V1:
	return 353;

    case SEC_OID_ANSIX962_EC_C2PNB368W1:
	return 353;

    case SEC_OID_SECG_EC_SECP384R1:
	return 384;

    case SEC_OID_SECG_EC_SECT409K1:
	return 407;
    case SEC_OID_SECG_EC_SECT409R1:
	return 409;

    case SEC_OID_ANSIX962_EC_C2TNB431R1:
	return 418;

    case SEC_OID_SECG_EC_SECP521R1:
	return 521;

    case SEC_OID_SECG_EC_SECT571K1:
    case SEC_OID_SECG_EC_SECT571R1:
	return 570;

    default:
	PORT_SetError(SEC_ERROR_UNSUPPORTED_ELLIPTIC_CURVE);
	return 0;
    }
}
