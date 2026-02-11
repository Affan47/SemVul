PKIX_PL_LdapClient_ResumeRequest(
        PKIX_PL_LdapClient *client,
        void **pNBIO,
        PKIX_List **pResponse,
        void *plContext)
{
        PKIX_ENTER(LDAPCLIENT, "PKIX_PL_LdapClient_ResumeRequest");
        PKIX_NULLCHECK_TWO(client, client->resumeFcn);

        PKIX_CHECK(client->resumeFcn
                (client, pNBIO, pResponse, plContext),
                PKIX_LDAPCLIENTRESUMEREQUESTFAILED);
cleanup:

        PKIX_RETURN(LDAPCLIENT);

}
