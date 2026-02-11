pkix_pl_HttpDefaultClient_ConnectContinue(
        PKIX_PL_HttpDefaultClient *client,
        PKIX_Boolean *pKeepGoing,
        void *plContext)
{
        PRErrorCode status;
        PKIX_Boolean keepGoing = PKIX_FALSE;
        PKIX_PL_Socket_Callback *callbackList = NULL;

        PKIX_ENTER
                (HTTPDEFAULTCLIENT,
                "pkix_pl_HttpDefaultClient_ConnectContinue");
        PKIX_NULLCHECK_ONE(client);

        callbackList = (PKIX_PL_Socket_Callback *)client->callbackList;

        PKIX_CHECK(callbackList->connectcontinueCallback
                (client->socket, &status, plContext),
                PKIX_SOCKETCONNECTCONTINUEFAILED);

        if (status == 0) {
                client->connectStatus = HTTP_CONNECTED;
                keepGoing = PKIX_TRUE;
        } else if (status != PR_IN_PROGRESS_ERROR) {
                PKIX_ERROR(PKIX_UNEXPECTEDERRORINESTABLISHINGCONNECTION);
        }

        *pKeepGoing = keepGoing;

cleanup:
        PKIX_RETURN(HTTPDEFAULTCLIENT);
}
