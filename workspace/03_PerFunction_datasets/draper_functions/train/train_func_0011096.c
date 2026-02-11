gen_linktype(proto)
	register int proto;
{
	struct block *b0, *b1;


	if (off_linktype == -1 && proto == ETHERTYPE_IP)
		return gen_true();

	switch (linktype) {

	case DLT_SLIP:
		return gen_false();

	case DLT_PPP:
		if (proto == ETHERTYPE_IP)
			proto = PPP_IP;
#ifdef INET6
		else if (proto == ETHERTYPE_IPV6)
			proto = PPP_IPV6;
#endif
		break;

	case DLT_PPP_BSDOS:
		switch (proto) {

		case ETHERTYPE_IP:
			b0 = gen_cmp(off_linktype, BPF_H, PPP_IP);
			b1 = gen_cmp(off_linktype, BPF_H, PPP_VJC);
			gen_or(b0, b1);
			b0 = gen_cmp(off_linktype, BPF_H, PPP_VJNC);
			gen_or(b1, b0);
			return b0;

#ifdef INET6
		case ETHERTYPE_IPV6:
			proto = PPP_IPV6;

			break;
#endif

		case ETHERTYPE_DN:
			proto = PPP_DECNET;
			break;

		case ETHERTYPE_ATALK:
			proto = PPP_APPLE;
			break;

		case ETHERTYPE_NS:
			proto = PPP_NS;
			break;
		}
		break;

	case DLT_NULL:

		if (proto == ETHERTYPE_IP)
			return (gen_cmp(0, BPF_W, (bpf_int32)htonl(AF_INET)));
#ifdef INET6
		else if (proto == ETHERTYPE_IPV6)
			return (gen_cmp(0, BPF_W, (bpf_int32)htonl(AF_INET6)));
#endif
		else
			return gen_false();
	}
	return gen_cmp(off_linktype, BPF_H, (bpf_int32)proto);
}
