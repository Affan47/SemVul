check_ssl(struct conn_entry* c) {
  X509 *p;
  SSL_CIPHER *cp;


  cp = SSL_get_current_cipher(c->srv_ssl);
  if(!(cp->algo_strength & SSL_MEDIUM) && !(cp->algo_strength & SSL_HIGH))
      problem(PROB_SSL_WEAK_CIPHER, c->q->req, 0,
        (u8*)SSL_CIPHER_get_name(cp),host_pivot(c->q->req->pivot), 0);


  p = SSL_get_peer_certificate(c->srv_ssl);

  if (p) {
    u32 cur_time = time(0);
    char *issuer, *host, *req_host;


    if (ASN1_UTCTIME_cmp_time_t(p->cert_info->validity->notBefore, cur_time)
        != -1 ||
        ASN1_UTCTIME_cmp_time_t(p->cert_info->validity->notAfter, cur_time)
        != 1)
      problem(PROB_SSL_CERT_DATE, c->q->req, 0, 0,
              host_pivot(c->q->req->pivot), 0);


    issuer = X509_NAME_oneline(p->cert_info->issuer,NULL,0);

    if (!issuer || !p->name || !strcmp(issuer, p->name))
      problem(PROB_SSL_SELF_CERT, c->q->req, 0, (u8*)issuer,
              host_pivot(c->q->req->pivot), 0);
    else
      problem(PROB_SSL_CERT, c->q->req, 0, (u8*)issuer,
              host_pivot(c->q->req->pivot), 0);

    free(issuer);


    host = strrchr(p->name, '=');
    req_host = (char*)c->q->req->host;

    if (host) {
      host++;
      if (host[0] == '*' && host[1] == '.') {
        host++;
        if (strlen(req_host) > strlen(host))
          req_host += strlen(req_host) - strlen(host);
      }
    }

    if (!host || strcasecmp(host, req_host))
      problem(PROB_SSL_BAD_HOST, c->q->req, 0, (u8*)host,
              host_pivot(c->q->req->pivot), 0);

    X509_free(p);

  } else problem(PROB_SSL_NO_CERT, c->q->req, 0, 0,
                 host_pivot(c->q->req->pivot), 0);

  c->ssl_checked = 1;
}
