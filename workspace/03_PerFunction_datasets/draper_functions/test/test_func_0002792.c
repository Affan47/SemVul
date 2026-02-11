gen_dnhostop(addr, dir, base_off)
	bpf_u_int32 addr;
	int dir;
	u_int base_off;
{
	struct block *b0, *b1, *b2, *tmp;
	u_int offset_lh;
	u_int offset_sh;

	switch (dir) {

	case Q_DST:
		offset_sh = 1;
		offset_lh = 7;
		break;

	case Q_SRC:
		offset_sh = 3;
		offset_lh = 15;
		break;

	case Q_AND:

		b0 = gen_dnhostop(addr, Q_SRC, base_off);
		b1 = gen_dnhostop(addr, Q_DST, base_off);
		gen_and(b0, b1);
		return b1;

	case Q_OR:
	case Q_DEFAULT:

		b0 = gen_dnhostop(addr, Q_SRC, base_off);
		b1 = gen_dnhostop(addr, Q_DST, base_off);
		gen_or(b0, b1);
		return b1;

	default:
		abort();
	}
	b0 = gen_linktype(ETHERTYPE_DN);

	tmp = gen_mcmp(base_off + 2, BPF_H,
	    (bpf_int32)ntohs(0x0681), (bpf_int32)ntohs(0x07FF));
	b1 = gen_cmp(base_off + 2 + 1 + offset_lh,
	    BPF_H, (bpf_int32)ntohs(addr));
	gen_and(tmp, b1);

	tmp = gen_mcmp(base_off + 2, BPF_B, (bpf_int32)0x06, (bpf_int32)0x7);
	b2 = gen_cmp(base_off + 2 + offset_lh, BPF_H, (bpf_int32)ntohs(addr));
	gen_and(tmp, b2);
	gen_or(b2, b1);

	tmp = gen_mcmp(base_off + 2, BPF_H,
	    (bpf_int32)ntohs(0x0281), (bpf_int32)ntohs(0x07FF));
	b2 = gen_cmp(base_off + 2 + 1 + offset_sh,
	    BPF_H, (bpf_int32)ntohs(addr));
	gen_and(tmp, b2);
	gen_or(b2, b1);

	tmp = gen_mcmp(base_off + 2, BPF_B, (bpf_int32)0x02, (bpf_int32)0x7);
	b2 = gen_cmp(base_off + 2 + offset_sh, BPF_H, (bpf_int32)ntohs(addr));
	gen_and(tmp, b2);
	gen_or(b2, b1);


	gen_and(b0, b1);
	return b1;
}
