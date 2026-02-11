sendIViewerGui(_WebClientConnection* cc)
{
    INFO2("[WS]: sendIViewerGui");

    sendData(cc, IVIEW_HEAD1);

    if (!cc->conn->serverIP) {
        ERROR2("[WS]: sendIViewerGui can not determine TCP address");
        return;
    }
    sendData(cc, cc->conn->serverIP->str);

    sendData(cc, IVIEW_HEAD2);

    int tcpPort = getIViewerTcpPort();
    if (tcpPort < 0) {
        ERROR2("[WS]: sendIViewerGui can not determine TCP port");
        return;
    }
    char num[16];
    sprintf(num,"%d", tcpPort);

    sendData(cc, num);
    sendData(cc, IVIEW_HEAD3);

    string_t* guiFile = stringNew(cc->conn->confDir ? cc->conn->confDir : ".");
    stringAppend(guiFile,"/Utils/anyremote.gui");

    struct stat statbuf;
    if (stat(guiFile->str, &statbuf) >= 0) {
        sendFile(cc, guiFile->str, &statbuf);
    } else {
        ERROR2("[WS]: sendIViewerGui can not open GUI file");
    }
    sendData(cc, IVIEW_TAIL);
}
