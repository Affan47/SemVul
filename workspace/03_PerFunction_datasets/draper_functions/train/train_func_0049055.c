http_server_check(http_server_t *server) {
  http_server_assert(server);

  int i;

   for (i = 0; i < server->num_clients; i++) {
      if ((server->clients[i].fd != -1) &&
          (server->clients[i].found < 2) &&
          (time(NULL) >= server->clients[i].fini)) {
        http_client_close(server, server->clients);
      }
   }
}
