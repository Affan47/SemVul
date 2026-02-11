sys_setxattr(struct tcb *tcp)
{
	if (entering(tcp)) {
		printpath(tcp, tcp->u_arg[0]);
		tprintf(", ");
		printstr(tcp, tcp->u_arg[1], -1);
		print_xattr_val(tcp, 0, tcp->u_arg[2], tcp->u_arg[3], tcp->u_arg[3]);
		tprintf(", ");
		printflags(xattrflags, tcp->u_arg[4], "XATTR_???");
	}
	return 0;
}
