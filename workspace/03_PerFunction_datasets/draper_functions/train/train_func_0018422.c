del_comm_server(Comm_server *serv) {
  Comm_server_client *client;
  Network_listener *l;

  free(serv->players);
  while ((client = list_pop(serv->clients)) != NULL) {
    del_comm_server_client(client);
  }
  while ((l = list_pop(serv->listeners)) != NULL) {
    del_network_listener(l);
  }
  del_list(serv->conns);
  del_list(serv->clients);
  del_list(serv->listeners);
  free(serv);
}
