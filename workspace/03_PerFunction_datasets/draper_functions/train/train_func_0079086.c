ctrl_c_handler(int signum)
{
	fflush(rhash_data.out);
	fprintf(rhash_data.log, "Interrupted by user...\n");
	fflush(rhash_data.log);


	if((opt.mode & (MODE_CHECK | MODE_CHECK_EMBEDDED)) && rhash_data.processed > 0) {
		print_check_stats();
		fflush(rhash_data.out);
	}


	if(prev_sigint_handler && prev_sigint_handler != SIG_ERR) {
		signal(signum, prev_sigint_handler);
		prev_sigint_handler(signum);
	}
	rsh_exit(1);
}
