FCGI_IsFastCGI(FCGP_Request* request) {
    static int isCGI = -1;

    if (request->requestPtr->listen_sock == FCGI_LISTENSOCK_FILENO) {
        if (isCGI == -1)
            isCGI = FCGX_IsCGI();
        return !isCGI;
    }


    return 1;
}
