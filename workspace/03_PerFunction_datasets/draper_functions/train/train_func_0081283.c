checkmatch(const struct filterent *e) {
    int r = 0;
#define	MUST(t)							\
    do if(!(e->t)) {						\
	fprintf(stderr, "%s missing from filter\n", #t);	\
	r++;							\
    } while(0)
    if(!e->subgroup)
	MUST(target);
    if(!e->groupname) {
	MUST(direction);
	MUST(iface);
    }
#undef MUST

    if((e->u.ports.src.minstr || e->u.ports.dst.minstr)
       && (e->proto.num != IPPROTO_TCP) && (e->proto.num != IPPROTO_UDP)) {
	fprintf(stderr, "can only use ports with tcp or udp\n");
	r++;
    }

    if(e->u.icmp && (e->proto.num != IPPROTO_ICMP)) {
	fprintf(stderr, "icmptype can only be used with icmp\n");
	r++;
    }

    if((e->rtype == LOCALONLY) && (e->target == MASQ)) {
	fprintf(stderr, "\"local\" and masquerading are incompatible\n");
	r++;
    }

    return r;
}
