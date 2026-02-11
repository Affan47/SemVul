filter_match(struct filter *f, const unsigned char *id,
             const unsigned char *prefix, unsigned short plen,
             const unsigned char *neigh, unsigned int ifindex, int proto)
{
    if(f->af) {
        if(plen >= 96 && v4mapped(prefix)) {
            if(f->af == AF_INET6) return 0;
        } else {
            if(f->af == AF_INET) return 0;
        }
    }
    if(f->id) {
        if(!id || memcmp(f->id, id, 8) != 0)
            return 0;
    }
    if(f->prefix) {
        if(!prefix || plen < f->plen || !in_prefix(prefix, f->prefix, f->plen))
            return 0;
    }
    if(f->plen_ge > 0 || f->plen_le < 128) {
        if(!prefix)
            return 0;
        if(plen > f->plen_le)
            return 0;
        if(plen < f->plen_ge)
            return 0;
    }
    if(f->neigh) {
        if(!neigh || memcmp(f->neigh, neigh, 16) != 0)
            return 0;
    }
    if(f->ifname) {
        if(!f->ifindex)
            return 0;
        if(!ifindex || f->ifindex != ifindex)
            return 0;
    }
    if(f->proto) {
        if(!proto || f->proto != proto)
            return 0;
    } else if(proto == RTPROT_BABEL_LOCAL) {
        return 0;
#ifdef __linux
    } else if(proto == RTPROT_BOOT) {
        return 0;
#endif
    }

    return 1;
}
