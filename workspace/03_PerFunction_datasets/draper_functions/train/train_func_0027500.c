print_mmap(struct tcb *tcp, long *u_arg, long long offset)
{
	if (entering(tcp)) {

		if (!u_arg[0])
			tprintf("NULL, ");
		else
			tprintf("%#lx, ", u_arg[0]);

		tprintf("%lu, ", u_arg[1]);

		printflags(mmap_prot, u_arg[2], "PROT_???");
		tprintf(", ");

#ifdef MAP_TYPE
		printxval(mmap_flags, u_arg[3] & MAP_TYPE, "MAP_???");
#ifdef TILE
		addflags(mmap_flags, addtileflags(u_arg[3] & ~MAP_TYPE));
#else
		addflags(mmap_flags, u_arg[3] & ~MAP_TYPE);
#endif
#else
		printflags(mmap_flags, u_arg[3], "MAP_???");
#endif

		tprintf(", ");
		printfd(tcp, u_arg[4]);

		tprintf(", %#llx", offset);
	}
	return RVAL_HEX;
}
