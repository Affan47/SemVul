pkix_pl_HttpDefaultClient_Create(
        const char *host,
        PRUint16 portnum,
        PKIX_PL_HttpDefaultClient **pClient,
        void *plContext)
{
        PKIX_PL_HttpDefaultClient *client = NULL;

        PKIX_ENTER(HTTPDEFAULTCLIENT, "PKIX_PL_HttpDefaultClient_Create");
        PKIX_NULLCHECK_TWO(pClient, host);


        PKIX_CHECK(PKIX_PL_Object_Alloc
                (PKIX_HTTPDEFAULTCLIENT_TYPE,
                sizeof (PKIX_PL_HttpDefaultClient),
                (PKIX_PL_Object **)&client,
                plContext),
                PKIX_COULDNOTCREATEHTTPDEFAULTCLIENTOBJECT);


        client->timeout = 0;
        client->connectStatus = HTTP_NOT_CONNECTED;
        client->portnum = portnum;
        client->bytesToWrite = 0;
        client->send_http_data_len = 0;
        client->rcv_http_data_len = 0;
        client->capacity = 0;
        client->filledupBytes = 0;
        client->responseCode = 0;
        client->maxResponseLen = 0;
        client->GETLen = 0;
        client->POSTLen = 0;
        client->pRcv_http_data_len = NULL;
        client->callbackList = NULL;
        client->GETBuf = NULL;
        client->POSTBuf = NULL;
        client->rcvBuf = NULL;


        client->host = PORT_Strdup(host);
        if (!client->host) {
            PKIX_ERROR(PKIX_ALLOCERROR);
        }
        client->path = NULL;
        client->rcvContentType = NULL;
        client->rcvHeaders = NULL;
        client->send_http_method = HTTP_POST_METHOD;
        client->send_http_content_type = NULL;
        client->send_http_data = NULL;
        client->rcv_http_response_code = NULL;
        client->rcv_http_content_type = NULL;
        client->rcv_http_headers = NULL;
        client->rcv_http_data = NULL;
        client->socket = NULL;


        client->plContext = plContext;

        *pClient = client;

cleanup:
        if (PKIX_ERROR_RECEIVED) {
                PKIX_DECREF(client);
        }

        PKIX_RETURN(HTTPDEFAULTCLIENT);
}
