pkix_pl_LdapDefaultClient_InitiateRequest(
        PKIX_PL_LdapClient *genericClient,
        LDAPRequestParams *requestParams,
        void **pPollDesc,
        PKIX_List **pResponse,
        void *plContext)
{
        PKIX_List *searchResponseList = NULL;
        SECItem *encoded = NULL;
        LDAPFilter *filter = NULL;
        PKIX_PL_LdapDefaultClient *client = 0;

        PKIX_ENTER
                (LDAPDEFAULTCLIENT,
                "pkix_pl_LdapDefaultClient_InitiateRequest");
        PKIX_NULLCHECK_FOUR(genericClient, requestParams, pPollDesc, pResponse);

        PKIX_CHECK(pkix_CheckType
                ((PKIX_PL_Object *)genericClient,
                PKIX_LDAPDEFAULTCLIENT_TYPE,
                plContext),
                PKIX_GENERICCLIENTNOTANLDAPDEFAULTCLIENT);

        client = (PKIX_PL_LdapDefaultClient *)genericClient;

        PKIX_CHECK(pkix_pl_LdapDefaultClient_MakeAndFilter
                (client->arena, requestParams->nc, &filter, plContext),
                PKIX_LDAPDEFAULTCLIENTMAKEANDFILTERFAILED);

        PKIX_CHECK(pkix_pl_LdapRequest_Create
                (client->arena,
                client->messageID++,
                requestParams->baseObject,
                requestParams->scope,
                requestParams->derefAliases,
                requestParams->sizeLimit,
                requestParams->timeLimit,
                PKIX_FALSE,
                filter,
                requestParams->attributes,
                &client->currentRequest,
                plContext),
                PKIX_LDAPREQUESTCREATEFAILED);


        PKIX_CHECK(PKIX_PL_HashTable_Lookup
                (client->cachePtr,
                (PKIX_PL_Object *)(client->currentRequest),
                (PKIX_PL_Object **)&searchResponseList,
                plContext),
                PKIX_HASHTABLELOOKUPFAILED);

        if (searchResponseList != NULL) {
                *pPollDesc = NULL;
                *pResponse = searchResponseList;
                PKIX_DECREF(client->currentRequest);
                goto cleanup;
        }


        PKIX_CHECK(pkix_pl_LdapRequest_GetEncoded
                (client->currentRequest, &encoded, plContext),
                PKIX_LDAPREQUESTGETENCODEDFAILED);

        client->sendBuf = encoded->data;
        client->bytesToWrite = encoded->len;

        PKIX_CHECK(pkix_pl_LdapDefaultClient_Dispatch(client, plContext),
                PKIX_LDAPDEFAULTCLIENTDISPATCHFAILED);


        if ((client->connectStatus == BOUND) &&
	    (client->entriesFound != NULL)) {
                *pPollDesc = NULL;
                *pResponse = client->entriesFound;
                client->entriesFound = NULL;
                PKIX_DECREF(client->currentRequest);
        } else {
                *pPollDesc = &client->pollDesc;
                *pResponse = NULL;
        }

cleanup:

        PKIX_RETURN(LDAPDEFAULTCLIENT);

}
