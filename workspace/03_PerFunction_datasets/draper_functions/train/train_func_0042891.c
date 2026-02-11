log_access(const struct connection *conn, const char *path) {
  const struct mg_connection *c = &conn->mg_conn;
  FILE *fp = (path == NULL) ?  NULL : fopen(path, "a+");
  char date[64], user[100];
  time_t now;

  if (fp == NULL) return;
  now = time(NULL);
  strftime(date, sizeof(date), "%d/%b/%Y:%H:%M:%S %z", localtime(&now));

  flockfile(fp);
  mg_parse_header(mg_get_header(&conn->mg_conn, "Authorization"), "username",
                  user, sizeof(user));
  fprintf(fp, "%s - %s [%s] \"%s %s%s%s HTTP/%s\" %d %" INT64_FMT,
          c->remote_ip, user[0] == '\0' ? "-" : user, date,
          c->request_method ? c->request_method : "-",
          c->uri ? c->uri : "-", c->query_string ? "?" : "",
          c->query_string ? c->query_string : "",
          c->http_version, c->status_code, conn->num_bytes_sent);
  log_header(c, "Referer", fp);
  log_header(c, "User-Agent", fp);
  fputc('\n', fp);
  fflush(fp);

  funlockfile(fp);
  fclose(fp);
}
