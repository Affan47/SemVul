pkix_pl_LdapDefaultClient_Destroy(
        PKIX_PL_Object *object,
        void *plContext)
{
        PKIX_Int32 bytesWritten = 0;
        PKIX_PL_LdapDefaultClient *client = NULL;
        PKIX_PL_Socket_Callback *callbackList = NULL;
        SECItem *encoded = NULL;

        PKIX_ENTER(LDAPDEFAULTCLIENT,
                    "pkix_pl_LdapDefaultClient_Destroy");
        PKIX_NULLCHECK_ONE(object);

        PKIX_CHECK(pkix_CheckType
                    (object, PKIX_LDAPDEFAULTCLIENT_TYPE, plContext),
                    PKIX_OBJECTNOTANLDAPDEFAULTCLIENT);

        client = (PKIX_PL_LdapDefaultClient *)object;

        switch (client->connectStatus) {
        case CONNECT_PENDING:
                break;
        case CONNECTED:
        case BIND_PENDING:
        case BIND_RESPONSE:
        case BIND_RESPONSE_PENDING:
        case BOUND:
        case SEND_PENDING:
        case RECV:
        case RECV_PENDING:
        case RECV_INITIAL:
        case RECV_NONINITIAL:
        case ABANDON_PENDING:
                if (client->bindAPI != NULL) {
                        PKIX_CHECK(pkix_pl_LdapDefaultClient_MakeUnbind
                                (client->arena,
                                ++(client->messageID),
                                &encoded,
                                plContext),
                                PKIX_LDAPDEFAULTCLIENTMAKEUNBINDFAILED);

                        callbackList =
                                (PKIX_PL_Socket_Callback *)(client->callbackList);
                        PKIX_CHECK(callbackList->sendCallback
                                (client->clientSocket,
                                encoded->data,
                                encoded->len,
                                &bytesWritten,
                                plContext),
                                PKIX_SOCKETSENDFAILED);
                }
                break;
        default:
                PKIX_ERROR(PKIX_LDAPDEFAULTCLIENTINILLEGALSTATE);
        }

        PKIX_DECREF(client->cachePtr);
        PKIX_DECREF(client->clientSocket);
        PKIX_DECREF(client->entriesFound);
        PKIX_DECREF(client->currentRequest);
        PKIX_DECREF(client->currentResponse);

        PKIX_CHECK(PKIX_PL_Free
		(client->rcvBuf, plContext), PKIX_FREEFAILED);

        PKIX_PL_NSSCALL
                (LDAPDEFAULTCLIENT,
                PORT_FreeArena,
                (client->arena, PR_FALSE));

cleanup:

        PKIX_RETURN(LDAPDEFAULTCLIENT);
}
