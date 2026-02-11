v5OutputUdpReply(fdInfoType *info,void *buf,int len,unsigned int flags,const void *from, int fromLen)
{
    double dbuf[65536/sizeof(double)];
    register v5UdpHeadType *head=(v5UdpHeadType*)dbuf;
    register char *c=(char*)dbuf+sizeof(v5UdpHeadType)-sizeof(head->destAddr);

    if (info->conn->ruleFlags&RF_LOG_RECORDS_CLIENT)
	dumpUDPData(info,buf,len,"OC");

    head->rsv=head->frag=0;
    c+=v5PutSin(from,fromLen,(v5HeadType*)head);
    if (head->rsv)
	return;

    if (c+len > (char*)dbuf+sizeof(dbuf))
	return;
    memcpy(c,buf,len), c+=len;

    info->UDP_SENDTO(info->fd,dbuf,c-(char*)dbuf,flags,&info->sin,sizeof(struct sockaddr_in));
    updateTime(info,out,len,now);
}
