print_response(char *msg) {
  char *tok, *sav[MAX_TOKENS];
  serv_response res;
  int count = 0;

  tok = strtok_r(msg, DELIM, sav);
  string2response(&res, tok);
  print_port(&res);

  while (NULL != (tok = strtok_r(NULL, DELIM, sav)) && count < MAX_TOKENS) {
    string2response(&res, tok);
    print_port(&res);
    count++;
  }

}
