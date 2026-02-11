lookup_proto(name, proto)
	register const char *name;
	register int proto;
{
	register int v;

	switch (proto) {

	case Q_DEFAULT:
	case Q_IP:
		v = pcap_nametoproto(name);
		if (v == PROTO_UNDEF)
			bpf_error("unknown ip proto '%s'", name);
		break;

	case Q_LINK:

		v = pcap_nametoeproto(name);
		if (v == PROTO_UNDEF)
			bpf_error("unknown ether proto '%s'", name);
		break;

	default:
		v = PROTO_UNDEF;
		break;
	}
	return v;
}
