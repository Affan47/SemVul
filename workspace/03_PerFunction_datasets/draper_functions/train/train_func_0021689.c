ss_match(struct sockaddr_storage *ss1,
                struct sockaddr_storage *ss2)
{
        size_t addrlen;
        enum ss_match_verdict ret = MATCH_NONE;
        void *addr1, *addr2;

        if (ss1->ss_family != ss2->ss_family)
                return ret;

        if (ss_get_port(ss1) == ss_get_port(ss2))
                ret = MATCH_PORT;

        if (ss1->ss_family == AF_INET) {
                addrlen = sizeof(struct in_addr);
                addr1 = ss_get_addr(ss1);
                addr2 = ss_get_addr(ss2);
        } else if (ss1->ss_family == AF_INET6) {
                addrlen = sizeof(struct in6_addr);
                addr1 = ss_get_addr6(ss1);
                addr2 = ss_get_addr6(ss2);
        } else {
                return MATCH_NONE;
        }

        if (!memcmp(addr1,addr2,addrlen)) {
                if (ret == MATCH_PORT)
                        ret = MATCH_BOTH;
                else
                        ret = MATCH_ADDRESS;
        }
        return ret;
}
