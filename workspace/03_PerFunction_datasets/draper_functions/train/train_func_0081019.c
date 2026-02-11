pkix_pl_LdapDefaultClient_ConnectContinue(
        PKIX_PL_LdapDefaultClient *client,
        PKIX_Boolean *pKeepGoing,
        void *plContext)
{
        PKIX_PL_Socket_Callback *callbackList;
        PRErrorCode status;
        PKIX_Boolean keepGoing = PKIX_FALSE;

        PKIX_ENTER
                (LDAPDEFAULTCLIENT,
                "pkix_pl_LdapDefaultClient_ConnectContinue");
        PKIX_NULLCHECK_ONE(client);

        callbackList = (PKIX_PL_Socket_Callback *)(client->callbackList);

        PKIX_CHECK(callbackList->connectcontinueCallback
                (client->clientSocket, &status, plContext),
                PKIX_SOCKETCONNECTCONTINUEFAILED);

        if (status == 0) {
                if (client->bindAPI != NULL) {
                        client->connectStatus = CONNECTED;
                } else {
                        client->connectStatus = BOUND;
                }
                keepGoing = PKIX_FALSE;
        } else if (status != PR_IN_PROGRESS_ERROR) {
                PKIX_ERROR(PKIX_UNEXPECTEDERRORINESTABLISHINGCONNECTION);
        }

        PKIX_CHECK(PKIX_PL_Object_InvalidateCache
                ((PKIX_PL_Object *)client, plContext),
                PKIX_OBJECTINVALIDATECACHEFAILED);

        *pKeepGoing = keepGoing;

cleanup:
        PKIX_RETURN(LDAPDEFAULTCLIENT);
}
