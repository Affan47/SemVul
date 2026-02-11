add_exprs_for_proto(int32_t proto, int32_t mask, Classification::Wordwise::Program &p, Vector<int> &tree)
{
    if (mask == 0xFF && proto == IP_PROTO_TCP_OR_UDP) {
	p.start_subtree(tree);
	p.add_insn(tree, IPFilter::offset_net + 8, htonl(IP_PROTO_TCP << 16), htonl(0x00FF0000));
	p.add_insn(tree, IPFilter::offset_net + 8, htonl(IP_PROTO_UDP << 16), htonl(0x00FF0000));
	p.finish_subtree(tree, Classification::c_or);
    } else if (mask == 0xFF && proto >= 256)
	;
    else
	p.add_insn(tree, IPFilter::offset_net + 8, htonl(proto << 16), htonl(mask << 16));
}
