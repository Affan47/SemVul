sys_mremap(struct tcb *tcp)
{
	if (entering(tcp)) {
		tprintf("%#lx, %lu, %lu, ", tcp->u_arg[0], tcp->u_arg[1],
			tcp->u_arg[2]);
		printflags(mremap_flags, tcp->u_arg[3], "MREMAP_???");
#ifdef MREMAP_FIXED
		if ((tcp->u_arg[3] & (MREMAP_MAYMOVE | MREMAP_FIXED)) ==
		    (MREMAP_MAYMOVE | MREMAP_FIXED))
			tprintf(", %#lx", tcp->u_arg[4]);
#endif
	}
	return RVAL_HEX;
}
