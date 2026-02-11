rfOpen(const string& szPort, const string& baudrate)
{
    int result;
    AsyncPort = (szPort[0] == '/');
    TncSysopMode = false;
    txrdy = false;
    APIRET rc;


    if (AsyncPort) {

        result = AsyncOpen(szPort, baudrate);
    }
#ifdef HAVE_LIBAX25
    else {

        result = SocketOpen(szPort, AprsPath);
    }
#else
    else {
        cerr << "AX.25 sockets are not supported by this executable" << endl;
        result = 1;
    }
#endif

    if (result != 0)
        return(result);

    CloseAsync = false;
    threadAck = false;


    if ((rc = pthread_create(&tidReadCom, NULL, rfReadCom, NULL)) < 0) {
        cerr << "Error: ReadCom thread creation failed. Error code = " << rc << endl;
        CloseAsync = true;
    }
    return(0);
}
