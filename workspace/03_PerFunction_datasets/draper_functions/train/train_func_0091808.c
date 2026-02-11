AddConnection(const SocketAddress& local,
                                        const SocketAddress& remote,
                                        VirtualSocket* remote_socket) {


  SocketAddress local_normalized(local.ipaddr().Normalized(),
                                 local.port());
  SocketAddress remote_normalized(remote.ipaddr().Normalized(),
                                  remote.port());
  SocketAddressPair address_pair(local_normalized, remote_normalized);
  connections_->insert(std::pair<SocketAddressPair,
                       VirtualSocket*>(address_pair, remote_socket));
}
