v5DoConnect(fdInfoType *client)
{
    register fdInfoType		*peer=client->peer;
    register connInfoType	*conn=client->conn;
    register int		outFd=peer->fd,res;
    struct sockaddr_in		sin;
    register v5HeadType		*req=conn->req;
    register int ret;

    outFd=peer->fd;

    if ((ret=v5GetSin(req,&sin,sizeof(sin)))!= SOCKS5_OK)
	return ret;
    peer->sin=sin;
    peer->TCP_INBOUND=simpleInbound;
    peer->TCP_OUTPUT =simpleOutput;
    clrSelect(client->fd,SL_READ);

    res=connect(outFd,(struct sockaddr*)&sin,sizeof(sin));

    if (res==0 || res<0 && errno==EINPROGRESS) {
	peer->TCP_SEND=v5ConnectSendReply;
	setSelect(outFd,SL_WRITE);
	clrSelect(outFd,SL_READ);
    } else {
	v5ConnectSendReply(outFd,NULL,0,0);
    }
    return SOCKS5_OK;
}
