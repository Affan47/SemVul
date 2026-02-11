FCGX_Free(FCGX_Request * request, int close)
{
    if (request == NULL)
        return;

    FCGX_FreeStream(&request->in);
    FCGX_FreeStream(&request->out);
    FCGX_FreeStream(&request->err);
    FreeParams(&request->paramsPtr);

    if (close) {
        OS_IpcClose(request->ipcFd);
        request->ipcFd = -1;
    }
}
