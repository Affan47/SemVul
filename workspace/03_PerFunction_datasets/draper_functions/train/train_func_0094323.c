httpOpenSendConnector(Http *http)
{
    HttpStage     *stage;

    mprLog(5, "Open send connector");
    if ((stage = httpCreateConnector(http, "sendConnector", HTTP_STAGE_ALL, NULL)) == 0) {
        return MPR_ERR_CANT_CREATE;
    }
    stage->open = httpSendOpen;
    stage->close = httpSendClose;
    stage->outgoingService = httpSendOutgoingService;
    http->sendConnector = stage;
    return 0;
}
