catch_url_init_std(int *port_prox, char *adr_prox) {
  T_SOC soc;
  int try_to_listen_to[] = { 8080, 3128, 80, 81, 82, 8081, 3129, 31337, 0, -1 };
  int i = 0;

  do {
    soc = catch_url_init(&try_to_listen_to[i], adr_prox);
    *port_prox = try_to_listen_to[i];
    i++;
  } while((soc == INVALID_SOCKET) && (try_to_listen_to[i] >= 0));
  return soc;
}
