CMSRC2CBCParam_get(hx509_context context, const hx509_crypto crypto,
		   const heim_octet_string *ivec, heim_octet_string *param)
{
    CMSRC2CBCParameter rc2params;
    const struct _RC2_params *p = crypto->param;
    int maximum_effective_key = 128;
    size_t size;
    int ret;

    memset(&rc2params, 0, sizeof(rc2params));

    if (p)
	maximum_effective_key = p->maximum_effective_key;

    switch(maximum_effective_key) {
    case 40:
	rc2params.rc2ParameterVersion = 160;
	break;
    case 64:
	rc2params.rc2ParameterVersion = 120;
	break;
    case 128:
	rc2params.rc2ParameterVersion = 58;
	break;
    }
    rc2params.iv = *ivec;

    ASN1_MALLOC_ENCODE(CMSRC2CBCParameter, param->data, param->length,
		       &rc2params, &size, ret);
    if (ret == 0 && size != param->length)
	_hx509_abort("Internal asn1 encoder failure");

    return ret;
}
