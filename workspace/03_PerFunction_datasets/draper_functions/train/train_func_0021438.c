Curl_read(struct connectdata *conn,
              curl_socket_t sockfd,
              char *buf,
              size_t sizerequested,
              ssize_t *n)
{
  ssize_t nread;
  size_t bytesfromsocket = 0;
  char *buffertofill = NULL;
  bool pipelining = (bool)(conn->data->multi &&
                     Curl_multi_canPipeline(conn->data->multi));


  int num = (sockfd == conn->sock[SECONDARYSOCKET]);

  *n=0;


  if(pipelining) {
    size_t bytestocopy = MIN(conn->buf_len - conn->read_pos, sizerequested);


    if (bytestocopy > 0) {
      memcpy(buf, conn->master_buffer + conn->read_pos, bytestocopy);
      conn->read_pos += bytestocopy;
      conn->bits.stream_was_rewound = FALSE;

      *n = (ssize_t)bytestocopy;
      return CURLE_OK;
    }


    bytesfromsocket = MIN(sizerequested, sizeof(conn->master_buffer));
    buffertofill = conn->master_buffer;
  }
  else {
    bytesfromsocket = MIN((long)sizerequested, conn->data->set.buffer_size ?
                          conn->data->set.buffer_size : BUFSIZE);
    buffertofill = buf;
  }

  if(conn->ssl[num].use) {
    nread = Curl_ssl_recv(conn, num, buffertofill, bytesfromsocket);

    if(nread == -1) {
      return -1;
    }
  }
#ifdef USE_LIBSSH2
  else if (conn->protocol & PROT_SCP) {
    nread = Curl_scp_recv(conn, num, buffertofill, bytesfromsocket);


  }
  else if (conn->protocol & PROT_SFTP) {
    nread = Curl_sftp_recv(conn, num, buffertofill, bytesfromsocket);
  }
#endif
  else {
    if(conn->sec_complete)
      nread = Curl_sec_read(conn, sockfd, buffertofill,
                            bytesfromsocket);
    else
      nread = sread(sockfd, buffertofill, bytesfromsocket);

    if(-1 == nread) {
      int err = Curl_sockerrno();
#ifdef USE_WINSOCK
      if(WSAEWOULDBLOCK == err)
#else
      if((EWOULDBLOCK == err) || (EAGAIN == err) || (EINTR == err))
#endif
        return -1;
    }
  }

  if (nread >= 0) {
    if(pipelining) {
      memcpy(buf, conn->master_buffer, nread);
      conn->buf_len = nread;
      conn->read_pos = nread;
    }

    *n += nread;
  }

  return CURLE_OK;
}
