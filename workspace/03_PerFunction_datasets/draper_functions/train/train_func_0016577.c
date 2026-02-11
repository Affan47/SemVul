acceptHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
    int cport, cfd;
    char cip[128];
    redisClient *c;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(mask);
    REDIS_NOTUSED(privdata);

    cfd = anetAccept(server.neterr, fd, cip, &cport);
    if (cfd == AE_ERR) {
        redisLog(REDIS_DEBUG,"Accepting client connection: %s", server.neterr);
        return;
    }
    redisLog(REDIS_DEBUG,"Accepted %s:%d", cip, cport);
    if ((c = createClient(cfd)) == NULL) {
        redisLog(REDIS_WARNING,"Error allocating resoures for the client");
        close(cfd);
        return;
    }


    if (server.maxclients && listLength(server.clients) > server.maxclients) {
        char *err = "-ERR max number of clients reached\r\n";


        (void) write(c->fd,err,strlen(err));
        freeClient(c);
        return;
    }
    server.stat_numconnections++;
}
