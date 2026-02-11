pkix_pl_LdapDefaultClient_VerifyBindResponse(
        PKIX_PL_LdapDefaultClient *client,
        PKIX_UInt32 bufLen,
        void *plContext)
{
        SECItem decode = {siBuffer, NULL, 0};
        SECStatus rv = SECFailure;
        LDAPMessage msg;
        LDAPBindResponse *ldapBindResponse = NULL;

        PKIX_ENTER
                (LDAPDEFAULTCLIENT,
                "pkix_pl_LdapDefaultClient_VerifyBindResponse");
        PKIX_NULLCHECK_TWO(client, client->rcvBuf);

        decode.data = (void *)(client->rcvBuf);
        decode.len = bufLen;

        PKIX_CHECK(pkix_pl_LdapDefaultClient_DecodeBindResponse
                (client->arena, &decode, &msg, &rv, plContext),
                PKIX_LDAPDEFAULTCLIENTDECODEBINDRESPONSEFAILED);

        if (rv == SECSuccess) {
                ldapBindResponse = &msg.protocolOp.op.bindResponseMsg;
                if (*(ldapBindResponse->resultCode.data) == SUCCESS) {
                        client->connectStatus = BOUND;
                } else {
                        PKIX_ERROR(PKIX_BINDREJECTEDBYSERVER);
                }
        } else {
                PKIX_ERROR(PKIX_CANTDECODEBINDRESPONSEFROMSERVER);
        }

cleanup:

        PKIX_RETURN(LDAPDEFAULTCLIENT);
}
