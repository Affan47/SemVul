send_ip_port_status(int sock, srv_conf *config, char *ip, unsigned int port) {
  int byte_count;
  char sending[MSG_SIZ] = { '\0' };
  serv_response res;
  conf_list *curr;

  memset(&res, 0, sizeof(res));
  memset(res.ip, 0, MAX_IP_LEN);

  strncpy(res.ip, ip, NCPY(strlen(ip)));
  res.port = port;

  res.protocol = TCP;
  if (NULL == (curr = query_port(ip, port, TCP, config))) {
    if (TRUE == is_free(ip, port, TCP)) {
      res.state = FREE;
    } else {
      res.state = INUSE;
    }
  } else {
    res.state = LOCKED;
  }

  res.status = OK;
  response2string(sending, &res);
  byte_count = send(sock, sending, MSG_SIZ, 0);
  if (byte_count < 0)
    printf("Error sending client a reply.\n");

  res.protocol = UDP;
  if (NULL == (curr = query_port(ip, port, UDP, config))) {
    if (TRUE == is_free(ip, port, UDP)) {
      res.state = FREE;
    } else {
      res.state = INUSE;
    }
  } else {
    res.state = LOCKED;
  }

  res.status = OK;
  response2string(sending, &res);
  byte_count = send(sock, sending, MSG_SIZ, 0);
  if (byte_count < 0)
    printf("Error sending client a reply.\n");
}
