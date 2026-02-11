sql_auth_init(void)
{
  const char* tmp;

  host = getenv("CVM_MYSQL_HOST");
  user = getenv("CVM_MYSQL_USER");
  pass = getenv("CVM_MYSQL_PASS");
  db = getenv("CVM_MYSQL_DB");
  tmp = getenv("CVM_MYSQL_PORT");
  port = tmp ? atoi(tmp) : 0;
  unix_socket = getenv("CVM_MYSQL_SOCKET");

  mysql_init(&mysql);
  if ((tmp = getenv("CVM_MYSQL_DEFAULT_FILE")) != 0)
    if (mysql_options(&mysql, MYSQL_READ_DEFAULT_FILE, tmp))
      return CVME_CONFIG;
  if ((tmp = getenv("CVM_MYSQL_DEFAULT_GROUP")) != 0)
    if (mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, tmp))
      return CVME_CONFIG;
  return do_connect();
}
