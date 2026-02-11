_get_token( id, tpname, tpvalue, tpsize )
    int   id, tpsize;
    char *tpname;
    char *tpvalue;
{
    int     sock;
    u_short this_op = TSH_ADVANCED_OP_GET_TOKEN;
    sng_map *link_pt;
    tsh_get_it out;
    tsh_get_ot1 in1;
    tsh_get_ot2 in2;

    this_op = htons(this_op) ;
    link_pt = handles[id];
    if ((sock = get_socket()) == -1)
    {
            perror("_get_token: get_socket error\n") ;
            close(sock);
            return(TSGET_ER) ;
    }
    if (!do_connect(sock, inet_addr(link_pt->cpu),
            link_pt->port))
    {
            perror("_get_token: TSH connection error\n") ;
            close(sock);
            return(TSGET_ER) ;
    }
    if (!writen(sock, (char *)&this_op, sizeof(u_short)))
    {
            perror("_get_token: Op code send error\n") ;
            close(sock);
            return(TSGET_ER) ;
    }
    strcpy(out.expr,tpname);
    out.host = sng_map_hd.host;
    out.port = link_pt->ret_port;
    out.len = htonl(tpsize);
    out.proc_id = htonl(getpid());

    if (!writen(sock, (char *)&out, sizeof(tsh_get_it)))
    {
            perror("_get_token: Length send error\n") ;
            close(sock);
            return(TSGET_ER);
    }

    if (!readn(sock, (char *)&in1, sizeof(tsh_get_ot1)))
    {
            perror("_get_token: read status error\n") ;
            close(sock);
            return(TSGET_ER) ;
    }

    if (ntohs(in1.status) != SUCCESS)
    {
            close(sock);
            if (tpsize == -1) return(0);
            sock = get_connection(link_pt->sd, 0) ;
    }

    if (!readn(sock, (char *)&in2, sizeof(tsh_get_ot2)))
    {
            perror("_get_token: tuple details read error\n") ;
            close(sock) ;
            return(-1);
    }

    strcpy(tpname,in2.name) ;
    tpsize = ntohl(in2.length) ;
    if (!readn(sock, tpvalue, tpsize))
    {
            perror("_get_token: tuple read error\n") ;
            close(sock);
            return(TSGET_ER);
    }

    close(sock) ;
    return(tpsize);
}
