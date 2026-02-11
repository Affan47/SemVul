ossl_asn1_tag_class(VALUE obj)
{
    VALUE s;
    int ret = -1;

    s = ossl_asn1_get_tag_class(obj);
    if(NIL_P(s)) ret = V_ASN1_UNIVERSAL;
    else if(SYMBOL_P(s)){
	if (SYM2ID(s) == sUNIVERSAL)
	    ret = V_ASN1_UNIVERSAL;
	else if (SYM2ID(s) == sAPPLICATION)
	    ret = V_ASN1_APPLICATION;
	else if (SYM2ID(s) == sCONTEXT_SPECIFIC)
	    ret = V_ASN1_CONTEXT_SPECIFIC;
	else if (SYM2ID(s) == sPRIVATE)
	    ret = V_ASN1_PRIVATE;
    }
    if(ret < 0){
	ossl_raise(eASN1Error, "invalid tag class");
    }

    return ret;
}
