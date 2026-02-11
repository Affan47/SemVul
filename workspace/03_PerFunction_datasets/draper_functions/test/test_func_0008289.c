waiting_socket(int family,int port)
{
    int sock;
    int ret;
    char portstr[8];
    struct addrinfo hints,*result = NULL;

    if(port < 0 || 0xffff < port) {
	display(MSDL_ERR,"internal: invalid port number\n");
	goto failed;
    }

    memset(portstr,0,8);
    snprintf(portstr,7,"%d",port);


    memset(&hints,0,sizeof(hints));
    hints.ai_family = family;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;


    ret = getaddrinfo(NULL,portstr,&hints,&result);
    if(ret != 0) {
	perror("getaddrinfo() failed");
	goto failed;
    }

    sock = socket(result->ai_family,result->ai_socktype,result->ai_protocol);
    if(sock < 0) {
	perror("socket() failed");
	goto failed;
    }


    ret = bind(sock,(struct sockaddr *)result->ai_addr,result->ai_addrlen);
    if(ret < 0) {
	perror("bind() failed");
	goto failed;
    }


    ret = listen(sock,1);
    if(ret < 0) {
	perror("listen() failed");
	goto failed;
    }

    freeaddrinfo(result);
    return sock;

  failed:
    if(result) freeaddrinfo(result);
    return -1;
}
