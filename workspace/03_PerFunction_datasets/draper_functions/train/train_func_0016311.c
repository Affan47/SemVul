pkix_pl_LdapRequest_AttrStringToBit(
        char *attrString,
        LdapAttrMask *pAttrBit,
        void *plContext)
{
        LdapAttrMask attrBit = 0;
        unsigned int attrLen = 0;

        PKIX_ENTER(LDAPREQUEST, "pkix_pl_LdapRequest_AttrStringToBit");
        PKIX_NULLCHECK_TWO(attrString, pAttrBit);

        attrLen = PL_strlen(attrString);


        if (attrLen == caAttrLen) {
                if (PORT_Strncasecmp(caAttr, attrString, attrLen) == 0) {
                        attrBit = LDAPATTR_CACERT;
                }
        } else if (attrLen == uAttrLen) {
                if (PORT_Strncasecmp(uAttr, attrString, attrLen) == 0) {
                        attrBit = LDAPATTR_USERCERT;
                }
        } else if (attrLen == ccpAttrLen) {
                if (PORT_Strncasecmp(ccpAttr, attrString, attrLen) == 0) {
                        attrBit = LDAPATTR_CROSSPAIRCERT;
                }
        } else if (attrLen == crlAttrLen) {
                if (PORT_Strncasecmp(crlAttr, attrString, attrLen) == 0) {
                        attrBit = LDAPATTR_CERTREVLIST;
                }
        } else if (attrLen == arlAttrLen) {
                if (PORT_Strncasecmp(arlAttr, attrString, attrLen) == 0) {
                        attrBit = LDAPATTR_AUTHREVLIST;
                }
        }

        *pAttrBit = attrBit;

        PKIX_RETURN(LDAPREQUEST);
}
