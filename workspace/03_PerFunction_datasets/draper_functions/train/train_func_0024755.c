openUxSocket(ConnectInfo* connInfo)
{
    DEBUG2("[DS]: Unix socket client mode. Use port %s", connInfo->portStr->str);
    if (unix_open_port(connInfo->portStr->str) < 0) {
    	printf("ERROR: open inputlircd socket\n");
    	return EXIT_NOK;
    }
    connInfo->state = PEER_CONNECTED;
    return EXIT_OK;
}
