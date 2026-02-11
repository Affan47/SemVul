main(int argc, char** argv)
{
  char* p;
  char* sid;
  char* nid;
  char* res;
  char* setcookie;

#if 1


  p = getenv("SERVER_SOFTWARE");
  if (p && !memcmp(p, "mini_httpd", sizeof("mini_httpd")-1)) {
    close(2);
    if (open("/var/tmp/zxid.stderr", O_WRONLY | O_CREAT | O_APPEND, 0666) != 2)
      exit(2);
  }
  fprintf(stderr, "=================== Running " ZXIDHLO " ===================\n");
#endif

  if (argc > 1) {
    fprintf(stderr, "This is a CGI script (written in C). No arguments are accepted.\n%s", help);
    exit(1);
  }

  res = zxid_simple(CONF, 0, 0x1fff);
  switch (res[0]) {
  default:
    ERR("Unknown zxid_simple() response(%s)", res);
  case 'd': break;
  }


  sid = strstr(res, "sesid: ");
  nid = strstr(res, "idpnid: ");
  setcookie = strstr(res, "setcookie: ");
  if (sid) {
    sid += sizeof("sesid: ") - 1;
    p = strchr(sid, '\n');
    if (p)
      *p = 0;
  }
  if (nid) {
    nid += sizeof("idpnid: ") - 1;
    p = strchr(nid, '\n');
    if (p)
      *p = 0;
  }
  if (setcookie) {
    setcookie += sizeof("setcookie: ") - 1;
    p = strchr(setcookie, '\n');
    if (p)
      *p = 0;
  }


  if (setcookie && !ONE_OF_2(*setcookie, '-', 0))
    printf("SET-COOKIE: %s\r\n", setcookie);
  printf("Content-Type: text/html\r\n\r\n");
  printf("<title>ZXID HELLO SP Mgmt</title>" ZXID_BODY_TAG "<h1>ZXID HELLO SP Management (user logged in, session active)</h1><pre>\n");
  printf("</pre><form method=post action=\"?o=P\">");


  if (sid) {
    printf("<input type=hidden name=s value=\"%s\">", sid);
    printf("<input type=submit name=gl value=\" Local Logout \">\n");
    printf("<input type=submit name=gr value=\" Single Logout (Redir) \">\n");
    printf("<input type=submit name=gs value=\" Single Logout (SOAP) \">\n");
    printf("<input type=submit name=gt value=\" Defederate (Redir) \">\n");
    printf("<input type=submit name=gu value=\" Defederate (SOAP) \"><br>\n");
    printf("sid(%s) nid(%s) <a href=\"?s=%s\">Reload</a> | "
	   "<a href=\"?o=v&s=%s\">PEP</a>", sid, nid?nid:"?!?", sid, sid);
  }

  printf("</form><hr>");
  printf("<a href=\"http://zxid.org/\">zxid.org</a>, %s", zxid_version_str());
  return 0;
}
