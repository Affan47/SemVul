dnsserv_resolved(entry_connection_t *conn,
                 int answer_type,
                 size_t answer_len,
                 const char *answer,
                 int ttl)
{
  struct evdns_server_request *req = conn->dns_server_request;
  const char *name;
  int err = DNS_ERR_NONE;
  if (!req)
    return;
  name = evdns_get_orig_address(req, answer_type,
                                conn->socks_request->address);


  if (ttl < 60)
    ttl = 60;


  if (answer_type == RESOLVED_TYPE_IPV6) {
    log_info(LD_APP, "Got an IPv6 answer; that's not implemented.");
    err = DNS_ERR_NOTIMPL;
  } else if (answer_type == RESOLVED_TYPE_IPV4 && answer_len == 4 &&
             conn->socks_request->command == SOCKS_COMMAND_RESOLVE) {
    evdns_server_request_add_a_reply(req,
                                     name,
                                     1, answer, ttl);
  } else if (answer_type == RESOLVED_TYPE_HOSTNAME &&
             answer_len < 256 &&
             conn->socks_request->command == SOCKS_COMMAND_RESOLVE_PTR) {
    char *ans = tor_strndup(answer, answer_len);
    evdns_server_request_add_ptr_reply(req, NULL,
                                       name,
                                       ans, ttl);
    tor_free(ans);
  } else if (answer_type == RESOLVED_TYPE_ERROR) {
    err = DNS_ERR_NOTEXIST;
  } else {
    err = DNS_ERR_SERVERFAILED;
  }

  evdns_server_request_respond(req, err);

  conn->dns_server_request = NULL;
}
