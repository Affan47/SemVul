really_send_packet(struct sockaddr *sin, int sinlen,
                   unsigned char hopcount, unsigned char original_hopcount,
                   const unsigned char *nonce,
                   const unsigned char *src, const unsigned char *dest,
                   const unsigned char *data, size_t datalen)
{
    struct iovec iovec[2];
    struct msghdr msg;
    unsigned char header[24];
    int rc, ret;

    header[0] = 43;
    header[1] = 1;
    header[2] = hopcount;
    header[3] = original_hopcount;
    memcpy(header + 4, nonce, 4);
    memcpy(header + 8, src, 8);
    memcpy(header + 16, dest ? dest : ones, 8);
    iovec[0].iov_base = (void*)header;
    iovec[0].iov_len = sizeof(header);
    iovec[1].iov_base = (void*)data;
    iovec[1].iov_len = datalen;

    memset(&msg, 0, sizeof(msg));
    msg.msg_iov = iovec;
    msg.msg_iovlen = 2;
    if(sin) {
        msg.msg_name = sin;
        msg.msg_namelen = sinlen;
        rc = sendmsg(protocol_socket, &msg, 0);
        if(rc < 0) {
            int save = errno;
            perror("send");
            errno = save;
            return -1;
        }
        return 1;
    } else {
        int i, saved_errno = EHOSTUNREACH;
        ret = -1;
        for(i = 0; i < numnetworks; i++) {
            struct sockaddr_in6 sin6;
            if(networks[i].ifindex <= 0)
                continue;
            memset(&sin6, 0, sizeof(sin6));
            sin6.sin6_family = AF_INET6;
            memcpy(&sin6.sin6_addr, &protocol_group, 16);
            sin6.sin6_port = htons(protocol_port);
            sin6.sin6_scope_id = networks[i].ifindex;
            msg.msg_name = (struct sockaddr*)&sin6;
            msg.msg_namelen = sizeof(sin6);
            rc = sendmsg(protocol_socket, &msg, 0);
            if(rc < 0) {
                saved_errno = errno;
                perror("send");

            } else {
                ret = 1;
            }
            errno = saved_errno;
        }
        return ret;
    }
}
