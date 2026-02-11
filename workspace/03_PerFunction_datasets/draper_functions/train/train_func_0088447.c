ocsp_SendEncodedRequest(const char *location, const SECItem *encodedRequest)
{
    char *hostname = NULL;
    char *path = NULL;
    PRUint16 port;
    SECStatus rv;
    PRFileDesc *sock = NULL;
    PRFileDesc *returnSock = NULL;
    char *header = NULL;
    char portstr[16];


    rv = ocsp_ParseURL(location, &hostname, &port, &path);
    if (rv != SECSuccess)
	goto loser;

    PORT_Assert(hostname != NULL);
    PORT_Assert(path != NULL);

    sock = ocsp_ConnectToHost(hostname, port);
    if (sock == NULL)
	goto loser;

    portstr[0] = '\0';
    if (port != 80) {
        PR_snprintf(portstr, sizeof(portstr), ":%d", port);
    }

    if (!encodedRequest) {
      header = PR_smprintf("GET %s HTTP/1.0\r\n"
                          "Host: %s%s\r\n\r\n",
                          path, hostname, portstr);
      if (header == NULL)
          goto loser;


      if (PR_Write(sock, header, (PRInt32) PORT_Strlen(header)) < 0)
          goto loser;
    }
    else {
      header = PR_smprintf("POST %s HTTP/1.0\r\n"
                          "Host: %s%s\r\n"
                          "Content-Type: application/ocsp-request\r\n"
                          "Content-Length: %u\r\n\r\n",
                          path, hostname, portstr, encodedRequest->len);
      if (header == NULL)
          goto loser;


      if (PR_Write(sock, header, (PRInt32) PORT_Strlen(header)) < 0)
          goto loser;

      if (PR_Write(sock, encodedRequest->data,
                  (PRInt32) encodedRequest->len) < 0)
          goto loser;
    }

    returnSock = sock;
    sock = NULL;

loser:
    if (header != NULL)
	PORT_Free(header);
    if (sock != NULL)
	PR_Close(sock);
    if (path != NULL)
	PORT_Free(path);
    if (hostname != NULL)
	PORT_Free(hostname);

    return returnSock;
}
