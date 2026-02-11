senderror(int clsock, REQUEST *req, int code, const char *message){
  CBDATUM *datum;
  datum = cbdatumopen(NULL, -1);
  cbdatumprintf(datum, "HTTP/1.0 %d %s\r\n", code, message);
  addservinfo(datum, req->now, 0);
  cbdatumprintf(datum, "Content-Type: text/plain; charset=UTF-8\r\n");
  cbdatumprintf(datum, "\r\n");
  if(req->method != HM_HEAD) cbdatumprintf(datum, "%s\n", message);
  est_sock_send_all(clsock, cbdatumptr(datum), cbdatumsize(datum));
  cbdatumclose(datum);
  log_print(LL_DEBUG, "[%s:%d]: %d %s", req->claddr, req->clport, code, message);
}
