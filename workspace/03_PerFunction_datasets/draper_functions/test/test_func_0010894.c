socket_server_get_local_sockaddr (rpc_transport_t *this, struct sockaddr *addr,
                                  socklen_t *addr_len, sa_family_t *sa_family)
{
        int32_t ret = -1;

        GF_VALIDATE_OR_GOTO ("socket", sa_family, err);
        GF_VALIDATE_OR_GOTO ("socket", addr, err);
        GF_VALIDATE_OR_GOTO ("socket", addr_len, err);

        ret = server_fill_address_family (this, &addr->sa_family);
        if (ret == -1) {
                goto err;
        }

        *sa_family = addr->sa_family;

        switch (addr->sa_family)
        {
        case AF_INET_SDP:
                addr->sa_family = AF_INET;

        case AF_INET:
        case AF_INET6:
        case AF_UNSPEC:
                ret = af_inet_server_get_local_sockaddr (this, addr, addr_len);
                break;

        case AF_UNIX:
                ret = af_unix_server_get_local_sockaddr (this, addr, addr_len);
                break;
        }

        if (*sa_family == AF_UNSPEC) {
                *sa_family = addr->sa_family;
        }

err:
        return ret;
}
