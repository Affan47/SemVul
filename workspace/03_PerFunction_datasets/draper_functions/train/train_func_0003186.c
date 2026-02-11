hydra_mysql_prepare_auth(char *login, char *pass) {
  unsigned char *response;
  unsigned long login_len = strlen(login) > 32 ? 32 : strlen(login);
  unsigned long response_len = 4   +
    2   +
    3   +
    login_len + 1 + 8  ;

  response = (unsigned char *) malloc(response_len + 4);
  if (response == NULL) {
    fprintf(stderr, "[ERROR] could not allocate memory\n");
    return NULL;
  }
  memset(response, 0, response_len + 4);

  *((unsigned long *) response) = response_len - 4;
  response[3] = 0x01;
  response[4] = 0x85;
  response[5] = 0x24;
  response[6] = response[7] = response[8] = 0x00;
  memcpy(&response[9], login, login_len);
  response[9 + login_len] = '\0';
  hydra_scramble((char *) &response[9 + login_len + 1], mysqlsalt, pass);

  return (char *) response;
}
