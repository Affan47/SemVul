AcceptConnection(talk_base::AsyncSocket* server_socket) {

  talk_base::SocketAddress accept_addr;
  talk_base::AsyncSocket* accepted_socket =
      server_socket->Accept(&accept_addr);
  if (accepted_socket != NULL) {


    ASSERT(server_sockets_[server_socket] == cricket::PROTO_TCP ||
           server_sockets_[server_socket] == cricket::PROTO_SSLTCP);
    if (server_sockets_[server_socket] == cricket::PROTO_SSLTCP) {
      accepted_socket = new talk_base::AsyncSSLServerSocket(accepted_socket);
    }
    talk_base::AsyncTCPSocket* tcp_socket =
        new talk_base::AsyncTCPSocket(accepted_socket, false);


    AddInternalSocket(tcp_socket);
  }
}
