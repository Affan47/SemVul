find_certificate_matching_pkcs7(PKCS7 *p7)
{
    int i;
    STACK_OF(PKCS7_RECIP_INFO) *recips;
    PERSONAL_CERT *x = NULL;

    recips = p7->d.enveloped->recipientinfo;

    for(i=0; i<sk_PKCS7_RECIP_INFO_num(recips); i++){
        PKCS7_RECIP_INFO	*ri;

        ri = sk_PKCS7_RECIP_INFO_value(recips, i);

        if((x=find_certificate_matching_recip_info(ri))!=0){
            break;
        }
    }

    return x;
}
