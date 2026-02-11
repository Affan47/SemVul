ftp_login(CONN *C, URL U)
{
  int  code = 120;
  char tmp[128];

  code = __response(C);
  if (! okay(code)) {
    NOTIFY(ERROR, "FTP: Server responded: %d", code);
    return FALSE;
  }

  snprintf(tmp, sizeof(tmp), "%s", (url_get_username(U)==NULL)?"anonymous":url_get_username(U));
  code = __request(C, "USER %s", tmp);
  if (code != 331) {
    if (okay(code)) return TRUE;
  }

  memset(tmp, '\0', sizeof(tmp));
  snprintf(tmp, sizeof(tmp), "%s", (url_get_password(U)==NULL)?"siege@joedog.org":url_get_password(U));
  code = __request(C, "PASS %s", tmp);
  return __in_range(code, 200, 299);
}
