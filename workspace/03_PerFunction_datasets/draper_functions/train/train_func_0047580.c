pkix_pl_LdapRequest_Hashcode(
        PKIX_PL_Object *object,
        PKIX_UInt32 *pHashcode,
        void *plContext)
{
        PKIX_UInt32 dataLen = 0;
        PKIX_UInt32 dindex = 0;
        PKIX_UInt32 sizeOfLength = 0;
        PKIX_UInt32 idLen = 0;
        const unsigned char *msgBuf = NULL;
        PKIX_PL_LdapRequest *ldapRq = NULL;

        PKIX_ENTER(LDAPREQUEST, "pkix_pl_LdapRequest_Hashcode");
        PKIX_NULLCHECK_TWO(object, pHashcode);

        PKIX_CHECK(pkix_CheckType(object, PKIX_LDAPREQUEST_TYPE, plContext),
                    PKIX_OBJECTNOTLDAPREQUEST);

        ldapRq = (PKIX_PL_LdapRequest *)object;

        *pHashcode = 0;


        if (ldapRq->encoded) {
                msgBuf = (const unsigned char *)ldapRq->encoded->data;

                if ((msgBuf[1] & 0x80) != 0) {
                        sizeOfLength = msgBuf[1] & 0x7F;
                        for (dindex = 0; dindex < sizeOfLength; dindex++) {
                                dataLen = (dataLen << 8) + msgBuf[dindex + 2];
                        }
                } else {
                        dataLen = msgBuf[1];
                }


                idLen = msgBuf[dindex + 3] + 2;
                dindex += idLen;
                dataLen -= idLen;
                msgBuf = &msgBuf[dindex + 2];

                PKIX_CHECK(pkix_hash(msgBuf, dataLen, pHashcode, plContext),
                        PKIX_HASHFAILED);
        }

cleanup:

        PKIX_RETURN(LDAPREQUEST);

}
