xmlSecGCryptHmacCheckId(xmlSecTransformPtr transform) {

#ifndef XMLSEC_NO_SHA1
    if(xmlSecTransformCheckId(transform, xmlSecGCryptTransformHmacSha1Id)) {
        return(1);
    } else
#endif

#ifndef XMLSEC_NO_SHA256
    if(xmlSecTransformCheckId(transform, xmlSecGCryptTransformHmacSha256Id)) {
        return(1);
    } else
#endif

#ifndef XMLSEC_NO_SHA384
    if(xmlSecTransformCheckId(transform, xmlSecGCryptTransformHmacSha384Id)) {
        return(1);
    } else
#endif

#ifndef XMLSEC_NO_SHA512
    if(xmlSecTransformCheckId(transform, xmlSecGCryptTransformHmacSha512Id)) {
        return(1);
    } else
#endif

#ifndef XMLSEC_NO_RIPEMD160
    if(xmlSecTransformCheckId(transform, xmlSecGCryptTransformHmacRipemd160Id)) {
        return(1);
    } else
#endif

#ifndef XMLSEC_NO_MD5
    if(xmlSecTransformCheckId(transform, xmlSecGCryptTransformHmacMd5Id)) {
        return(1);
    } else
#endif


    {
        return(0);
    }


    return(0);
}
