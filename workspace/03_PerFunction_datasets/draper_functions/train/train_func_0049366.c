gen_atmfield_code(atmfield, jvalue, jtype, reverse)
	int atmfield;
	bpf_int32 jvalue;
	bpf_u_int32 jtype;
	int reverse;
{
	struct block *b0;

	switch (atmfield) {

	case A_VPI:
		if (!is_atm)
			bpf_error("'vpi' supported only on raw ATM");
		if (off_vpi == (u_int)-1)
			abort();
		b0 = gen_ncmp(OR_LINK, off_vpi, BPF_B, 0xffffffff, jtype,
		    reverse, jvalue);
		break;

	case A_VCI:
		if (!is_atm)
			bpf_error("'vci' supported only on raw ATM");
		if (off_vci == (u_int)-1)
			abort();
		b0 = gen_ncmp(OR_LINK, off_vci, BPF_H, 0xffffffff, jtype,
		    reverse, jvalue);
		break;

	case A_PROTOTYPE:
		if (off_proto == (u_int)-1)
			abort();
		b0 = gen_ncmp(OR_LINK, off_proto, BPF_B, 0x0f, jtype,
		    reverse, jvalue);
		break;

	case A_MSGTYPE:
		if (off_payload == (u_int)-1)
			abort();
		b0 = gen_ncmp(OR_LINK, off_payload + MSG_TYPE_POS, BPF_B,
		    0xffffffff, jtype, reverse, jvalue);
		break;

	case A_CALLREFTYPE:
		if (!is_atm)
			bpf_error("'callref' supported only on raw ATM");
		if (off_proto == (u_int)-1)
			abort();
		b0 = gen_ncmp(OR_LINK, off_proto, BPF_B, 0xffffffff,
		    jtype, reverse, jvalue);
		break;

	default:
		abort();
	}
	return b0;
}
