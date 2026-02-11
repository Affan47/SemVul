ntb_connection_connect(const struct ntb_netaddress *address,
                       struct ntb_network_stats *nw_stats,
                       struct ntb_error **error)
{
        struct ntb_netaddress_native native_address;
        char *address_string;
        int sock;

        ntb_netaddress_to_native(address, &native_address);

        sock = socket(native_address.sockaddr.sa_family == AF_INET6 ?
                      PF_INET6 : PF_INET,
                      SOCK_STREAM,
                      0);
        if (sock == -1) {
                ntb_file_error_set(error,
                                   errno,
                                   "Failed to create socket: %s",
                                   strerror(errno));
                return NULL;
        }

        if (!ntb_socket_set_nonblock(sock, error)) {
                ntb_close(sock);
                return NULL;
        }

        if (connect(sock,
                    &native_address.sockaddr,
                    native_address.length) == -1 &&
            errno != EINPROGRESS) {
                address_string = ntb_netaddress_to_string(address);
                ntb_file_error_set(error,
                                   errno,
                                   "Failed to connect to %s: %s",
                                   address_string,
                                   strerror(errno));
                ntb_free(address_string);
                ntb_close(sock);
                return NULL;
        }

        return ntb_connection_new_for_socket(sock, address, nw_stats);
}
