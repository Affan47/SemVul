xtables_init(void)
{
	xtables_libdir = getenv("XTABLES_LIBDIR");
	if (xtables_libdir != NULL)
		return;
	xtables_libdir = getenv("IPTABLES_LIB_DIR");
	if (xtables_libdir != NULL) {
		fprintf(stderr, "IPTABLES_LIB_DIR is deprecated, "
		        "use XTABLES_LIBDIR.\n");
		return;
	}


	xtables_libdir = getenv("IP6TABLES_LIB_DIR");
	if (xtables_libdir != NULL) {
		fprintf(stderr, "IP6TABLES_LIB_DIR is deprecated, "
		        "use XTABLES_LIBDIR.\n");
		return;
	}
	xtables_libdir = XTABLES_LIBDIR;
}
