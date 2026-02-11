gf_rdma_client_bind (rpc_transport_t *this,
                     struct sockaddr *sockaddr,
                     socklen_t *sockaddr_len,
                     int sock)
{
        int ret = 0;

        *sockaddr_len = sizeof (struct sockaddr_in6);
        switch (sockaddr->sa_family)
        {
        case AF_INET_SDP:
        case AF_INET:
                *sockaddr_len = sizeof (struct sockaddr_in);

        case AF_INET6:
                ret = af_inet_bind_to_port_lt_ceiling (sock, sockaddr,
                                                       *sockaddr_len,
                                                       CLIENT_PORT_CEILING);
                if (ret == -1) {
                        gf_log (this->name, GF_LOG_WARNING,
                                "cannot bind inet socket (%d) to port "
                                "less than %d (%s)",
                                sock, CLIENT_PORT_CEILING, strerror (errno));
                        ret = 0;
                }
                break;

        case AF_UNIX:
                *sockaddr_len = sizeof (struct sockaddr_un);
                ret = af_unix_client_bind (this, (struct sockaddr *)sockaddr,
                                           *sockaddr_len, sock);
                break;

        default:
                gf_log (this->name, GF_LOG_ERROR,
                        "unknown address family %d", sockaddr->sa_family);
                ret = -1;
                break;
        }

        return ret;
}
