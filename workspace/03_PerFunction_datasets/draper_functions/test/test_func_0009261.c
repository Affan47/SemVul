xmlSecOpenSSLEvpDigestCheckId(xmlSecTransformPtr transform) {

#ifndef XMLSEC_NO_MD5
    if(xmlSecTransformCheckId(transform, xmlSecOpenSSLTransformMd5Id)) {
        return(1);
    } else
#endif

#ifndef XMLSEC_NO_RIPEMD160
    if(xmlSecTransformCheckId(transform, xmlSecOpenSSLTransformRipemd160Id)) {
        return(1);
    } else
#endif

#ifndef XMLSEC_NO_SHA1
    if(xmlSecTransformCheckId(transform, xmlSecOpenSSLTransformSha1Id)) {
        return(1);
    } else
#endif

#ifndef XMLSEC_NO_SHA224
    if(xmlSecTransformCheckId(transform, xmlSecOpenSSLTransformSha224Id)) {
        return(1);
    } else
#endif

#ifndef XMLSEC_NO_SHA256
    if(xmlSecTransformCheckId(transform, xmlSecOpenSSLTransformSha256Id)) {
        return(1);
    } else
#endif

#ifndef XMLSEC_NO_SHA384
    if(xmlSecTransformCheckId(transform, xmlSecOpenSSLTransformSha384Id)) {
        return(1);
    } else
#endif

#ifndef XMLSEC_NO_SHA512
    if(xmlSecTransformCheckId(transform, xmlSecOpenSSLTransformSha512Id)) {
        return(1);
    } else
#endif

#ifndef XMLSEC_NO_GOST
    if(xmlSecTransformCheckId(transform, xmlSecOpenSSLTransformGostR3411_94Id)) {
        return(1);
    } else
#endif

#ifndef XMLSEC_NO_GOST2012
    if(xmlSecTransformCheckId(transform, xmlSecOpenSSLTransformGostR3411_2012_256Id)) {
        return(1);
    } else

    if(xmlSecTransformCheckId(transform, xmlSecOpenSSLTransformGostR3411_2012_512Id)) {
        return(1);
    } else
#endif

    {
        return(0);
    }

    return(0);
}
