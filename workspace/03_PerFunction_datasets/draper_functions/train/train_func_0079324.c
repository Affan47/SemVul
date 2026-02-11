set_defaults(void) {

	debug_m       = FALSE;
	preload_m     = FALSE;
	report_aggr_m = FALSE;
	do_html       = FALSE;
	isig_m	      = 0;
	pcapoffset_m  = 0;

	started_m     = (time_t) 0;

	mask_m	      = 24;
	cycle_m	      = 60;
	rcycle_m      = 300;
	thresh_m      = 7.0;
	fork_m	      = FALSE;
	top_m	      = 0;
	promisc_m     = TRUE;
	niplist_m     = 0;
	lenadj_m      = 0;


	FREE(config_m);
	FREE(pcapdev_m);
	FREE(pcapfile_m);
	FREE(filtercmd_m);
	FREE(repfname_m);
	FREE(htmlfname_m);
	FREE(htmltitle_m);
	FREE(mailto_m);
	FREE(mailfoot_m);
	FREE(iplist_m);


	FREE(mtastring_m);
	mtastring_m = strdup(MTASTR_DEF);

}
