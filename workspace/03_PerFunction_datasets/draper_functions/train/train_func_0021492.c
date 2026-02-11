startCgi(HttpQueue *q)
{
    HttpRx          *rx;
    HttpTx          *tx;
    HttpConn        *conn;
    MprCmd          *cmd;
    cchar           *baseName;
    char            **argv, **envv, *fileName;
    int             argc, varCount, count;

    argv = 0;
    argc = 0;
    conn = q->conn;
    rx = conn->rx;
    tx = conn->tx;

    mprLog(5, "CGI: Start");


    cmd = q->queueData = mprCreateCmd(conn->dispatcher);

    if (conn->http->forkCallback) {
        cmd->forkCallback = conn->http->forkCallback;
        cmd->forkData = conn->http->forkData;
    }

    argc = 1;
    buildArgs(conn, cmd, &argc, &argv);
    fileName = argv[0];

    baseName = mprGetPathBase(fileName);
    if (strncmp(baseName, "nph-", 4) == 0 ||
            (strlen(baseName) > 4 && strcmp(&baseName[strlen(baseName) - 4], "-nph") == 0)) {

        cmd->userFlags |= MA_CGI_SEEN_HEADER;
    }


    varCount = mprGetHashLength(rx->headers) + mprGetHashLength(rx->svars);
    if (rx->params) {
        varCount += mprGetHashLength(rx->params);
    }
    if ((envv = mprAlloc((varCount + 1) * sizeof(char*))) != 0) {
        count = copyVars(envv, 0, rx->params, "");
        count = copyVars(envv, 0, rx->svars, "");
        count = copyVars(envv, count, rx->headers, "HTTP_");
        mprAssert(count <= varCount);
    }
    cmd->stdoutBuf = mprCreateBuf(HTTP_BUFSIZE, HTTP_BUFSIZE);
    cmd->stderrBuf = mprCreateBuf(HTTP_BUFSIZE, HTTP_BUFSIZE);

    mprSetCmdDir(cmd, mprGetPathDir(fileName));
    mprSetCmdCallback(cmd, cgiCallback, tx);

    if (mprStartCmd(cmd, argc, argv, envv, MPR_CMD_IN | MPR_CMD_OUT | MPR_CMD_ERR) < 0) {
        httpError(conn, HTTP_CODE_SERVICE_UNAVAILABLE, "Can't run CGI process: %s, URI %s", fileName, rx->uri);
    }
}
