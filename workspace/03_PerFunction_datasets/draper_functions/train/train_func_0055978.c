main(int argc, char ** argv)
#endif
{
	_dropbear_exit = svr_dropbear_exit;
	_dropbear_log = svr_dropbear_log;

	disallow_core();


	svr_getopts(argc, argv);

#ifdef INETD_MODE

	if (svr_opts.inetdmode) {
		main_inetd();

	}
#endif

#ifdef NON_INETD_MODE
	main_noinetd();

#endif

	dropbear_exit("Compiled without normal mode, can't run without -i\n");
	return -1;
}
