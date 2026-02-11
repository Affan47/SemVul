print_axfr(FILE *file, const u_char *msg, size_t msglen) {
	ns_msg handle;

	if (ns_initparse(msg, msglen, &handle) < 0) {
		fprintf(file, ";; ns_initparse: %s\n", strerror(errno));
		return (ns_r_formerr);
	}
	if (ns_msg_getflag(handle, ns_f_rcode) != ns_r_noerror)
		return (ns_msg_getflag(handle, ns_f_rcode));


	if (ns_msg_count(handle, ns_s_an) == 0)
		return (NO_INFO);

#ifdef PROTOCOLDEBUG
	printf(";;; (message of %d octets has %d answers)\n",
	       msglen, ns_msg_count(handle, ns_s_an));
#endif
	for (;;) {
		static char origin[NS_MAXDNAME], name_ctx[NS_MAXDNAME];
		const char *name;
		char buf[2048];
		ns_rr rr;

		if (ns_parserr(&handle, ns_s_an, -1, &rr)) {
			if (errno != ENODEV) {
				fprintf(file, ";; ns_parserr: %s\n",
					strerror(errno));
				return (FORMERR);
			}
			break;
		}
		name = ns_rr_name(rr);
		if (origin[0] == '\0' && name[0] != '\0') {
			if (strcmp(name, ".") != 0)
				strcpy(origin, name);
			fprintf(file, "$ORIGIN %s.\n", origin);
			if (strcmp(name, ".") == 0)
				strcpy(origin, name);
			if (res.pfcode & RES_PRF_TRUNC)
				strcpy(name_ctx, "@");
		}
		if (ns_sprintrr(&handle, &rr,
				(res.pfcode & RES_PRF_TRUNC) ? name_ctx : NULL,
				(res.pfcode & RES_PRF_TRUNC) ? origin : NULL,
				buf, sizeof buf) < 0) {
			fprintf(file, ";; ns_sprintrr: %s\n", strerror(errno));
			return (FORMERR);
		}
		strcpy(name_ctx, name);
		fputs(buf, file);
		fputc('\n', file);
	}
	return (SUCCESS);
}
