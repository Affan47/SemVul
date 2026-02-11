af_inet_bind_to_port_lt_ceiling (int fd, struct sockaddr *sockaddr,
                                 socklen_t sockaddr_len, int ceiling)
{
        int32_t        ret        = -1;
        uint16_t      port        = ceiling - 1;

        gf_boolean_t  ports[1024] = {_gf_false,};
        int           i           = 0;

        ret = gf_process_reserved_ports (ports);
        if (ret != 0) {
                for (i = 0; i < 1024; i++)
                        ports[i] = _gf_false;
        }

        while (port)
        {
                switch (sockaddr->sa_family)
                {
                case AF_INET6:
                        ((struct sockaddr_in6 *)sockaddr)->sin6_port = htons (port);
                        break;

                case AF_INET_SDP:
                case AF_INET:
                        ((struct sockaddr_in *)sockaddr)->sin_port = htons (port);
                        break;
                }

                if (ports[port] == _gf_true) {
                        port--;
                        continue;
                }
                ret = bind (fd, sockaddr, sockaddr_len);

                if (ret == 0)
                        break;

                if (ret == -1 && errno == EACCES)
                        break;

                port--;
        }

        return ret;
}
