v4DoConnect(fdInfoType *client,v4HeadType *req)
{
    struct sockaddr_in		sin;
    register fdInfoType		*peer=client->peer;
    register int		outFd=peer->fd;
    register int		res;

    clrSelect(client->fd,SL_READ);

    memset(&sin,0,sizeof(sin));
    sin.sin_family=AF_INET;
    sin.sin_addr.s_addr=req->destIP;
    sin.sin_port=req->port;

    peer->sin=sin;
    peer->TCP_INBOUND=simpleInbound;
    peer->TCP_OUTPUT =simpleOutput;

    setSelect(outFd,SL_READ|SL_EXCP);

    res=connect(outFd,(struct sockaddr*)&sin,sizeof(sin));

    if (res==0 || res<0 && errno==EINPROGRESS) {
	peer->TCP_SEND=v4ConnectSendReply;
	setSelect(outFd,SL_WRITE);
    } else {
	v4ConnectSendReply(outFd,(const void *)NULL,0,0);
    }
}
