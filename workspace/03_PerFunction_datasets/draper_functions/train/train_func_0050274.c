dev_connect(enum conn_type type)
{
    int fd;
    struct addrinfo hints, *ai, *ai0;
    int i;
    char *port;

    switch(type){
        case CONN_CTRL: port = PORT_CTRL; break;
        case CONN_DATA: port = PORT_DATA; break;
    }

    DEBUG("DEVICE: dev_connect(%s:%s)\n", HOSTNAME, port);


    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if((i = getaddrinfo(HOSTNAME , port, &hints, &ai0)) != 0){
        fprintf(stderr, "Unable to look up IP address: %s\n", gai_strerror(i));
        return -1;
    }

    for(ai = ai0; ai != NULL; ai = ai->ai_next){
        fd = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
        if(fd == -1){
            continue;
        }

      if(connect(fd, ai->ai_addr, ai->ai_addrlen) == -1){
          close(fd);
          continue;
      }

      break;
    }

    if(ai == NULL){
        perror("Unable to connect to device");
        return -1;
    }

    return fd;
}
