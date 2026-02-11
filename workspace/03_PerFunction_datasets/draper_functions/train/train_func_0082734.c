handle_stream_transport(bgav_stream_t * s,
                                   const char * transport, int tcp)
  {
  const char * var;
  int var_len = 0;
  struct addrinfo * addr;
  int server_ports[2] = { 0, 0 };
  int client_ports[2] = { 0, 0 };

  rtp_stream_priv_t * sp = s->priv;

  if(!tcp)
    {
    if(!(var = get_answer_var(transport, "client_port=", &var_len)) ||
       !rtp_parse_range(var, client_ports))
      {
      return 0;
      }
    bgav_log(s->opt, BGAV_LOG_INFO, LOG_DOMAIN, "Client ports: %d %d\n",
             client_ports[0], client_ports[1]);

    if(!(var = get_answer_var(transport, "server_port=", &var_len)) ||
       !rtp_parse_range(var, server_ports))

      return 0;

    bgav_log(s->opt, BGAV_LOG_INFO, LOG_DOMAIN, "Server ports: %d %d\n",
             server_ports[0], server_ports[1]);

    if((var = get_answer_var(transport, "source=", &var_len)))
      {
      char * ip = bgav_strndup(var, var + var_len);
      addr = bgav_hostbyname(s->opt, ip, server_ports[0], SOCK_DGRAM, 0);
      if(!addr)
        {
        free(ip);
        return 0;
        }
      if(connect(sp->rtp_fd, addr->ai_addr, addr->ai_addrlen)<0)
        {
        free(ip);
        return 0;
        }
      freeaddrinfo(addr);

      addr = bgav_hostbyname(s->opt, ip, server_ports[1], SOCK_DGRAM, 0);
      if(!addr)
        {
        free(ip);
        return 0;
        }

      if(connect(sp->rtcp_fd, addr->ai_addr, addr->ai_addrlen)<0)
        {
        free(ip);
        return 0;
        }

      freeaddrinfo(addr);

      bgav_log(s->opt, BGAV_LOG_INFO, LOG_DOMAIN, "Server address: %s\n", ip);
      free(ip);
      }
    else
      return 0;

    }


  if((var = get_answer_var(transport, "ssrc=", &var_len)))
    sp->server_ssrc = strtoul(var, NULL, 16);

  bgav_log(s->opt, BGAV_LOG_INFO, LOG_DOMAIN, "ssrc: %08x\n",
           sp->server_ssrc);

  return 1;
  }
