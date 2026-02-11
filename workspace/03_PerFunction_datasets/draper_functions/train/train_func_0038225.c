fsp_open_session(const char *host,unsigned short port,const char *password)
{
    FSP_SESSION *s;
    int fd;
    struct addrinfo hints,*res;
    char port_s[6];
    struct sockaddr_in *addrin;
    FSP_LOCK *lock;

    memset (&hints, 0, sizeof (hints));

    hints.ai_family = PF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    if (port == 0)
        strcpy(port_s,"fsp");
    else
        sprintf(port_s,"%hu",port);

    if ( getaddrinfo(host,port_s,&hints,&res) )
    {
        return NULL;
    }


    fd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    if ( fd < 0)
        return NULL;


    if( connect(fd, res->ai_addr, res->ai_addrlen))
    {
        close(fd);
        return NULL;
    }


    s=calloc(1,sizeof(FSP_SESSION));
    if ( !s )
    {
        close(fd);
        errno = ENOMEM;
        return NULL;
    }

    lock=malloc(sizeof(FSP_LOCK));

    if ( !lock )
    {
        close(fd);
        free(s);
        errno = ENOMEM;
        return NULL;
    }

    s->lock=lock;


    addrin = (struct sockaddr_in *)res->ai_addr;
    if ( client_init_key( (FSP_LOCK *)s->lock,addrin->sin_addr.s_addr,ntohs(addrin->sin_port)))
    {
        free(s);
        close(fd);
        free(lock);
        return NULL;
    }

    s->fd=fd;
    s->timeout=300000;
    s->maxdelay=60000;
    s->seq=random() & 0xfff8;
    if ( password )
        s->password = strdup(password);
    return s;
}
