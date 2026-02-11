open_socket(char *node)
{
    int                  sockfd;
    struct nodeent      *np;
    char                *local_user;
    int                  i;
    struct sockaddr_dn   sockaddr;
    struct accessdata_dn accessdata;

    if ((sockfd=socket(AF_DECnet,SOCK_SEQPACKET,DNPROTO_NSP)) == -1)
    {
	return -1;
    }

    if ( (np=getnodebyname(node)) == NULL)
    {
	errno  = EHOSTUNREACH;
	return -1;
    }

    memset(&accessdata, 0, sizeof(accessdata));


    local_user = cuserid(NULL);
    if (!local_user || local_user == (char *)0xffffffff)
	local_user = getenv("LOGNAME");
    if (!local_user) local_user = getenv("USER");
    if (local_user)
    {

	strcpy((char *)accessdata.acc_acc, local_user);
	accessdata.acc_accl = strlen((char *)accessdata.acc_acc);
	for (i=0; i<accessdata.acc_accl; i++)
	    accessdata.acc_acc[i] = toupper(accessdata.acc_acc[i]);
    }

    if (setsockopt(sockfd,DNPROTO_NSP,SO_CONACCESS,&accessdata,
		   sizeof(accessdata)) < 0)
    {
	 return -1;
    }
    sockaddr.sdn_family    = AF_DECnet;
    sockaddr.sdn_flags	   = 0x00;
    sockaddr.sdn_objnum	   = MAIL_OBJECT;
    sockaddr.sdn_objnamel  = 0x00;
    sockaddr.sdn_add.a_len = 0x02;
    memcpy(sockaddr.sdn_add.a_addr, np->n_addr,2);

    if (connect(sockfd, (struct sockaddr *)&sockaddr,
		sizeof(sockaddr)) < 0)
    {
	return -1;
    }

    return sockfd;
}
