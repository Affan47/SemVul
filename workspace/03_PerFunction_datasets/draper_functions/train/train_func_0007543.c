usage (int do_exit)
{
	printf ("Log profiler version %d.%d (format: %d)\n", LOG_VERSION_MAJOR, LOG_VERSION_MINOR, LOG_DATA_VERSION);
	printf ("Usage: mono --profile=log[:OPTION1[,OPTION2...]] program.exe\n");
	printf ("Options:\n");
	printf ("\thelp             show this usage info\n");
	printf ("\t[no]alloc        enable/disable recording allocation info\n");
	printf ("\t[no]calls        enable/disable recording enter/leave method events\n");
	printf ("\theapshot[=MODE]  record heap shot info (by default at each major collection)\n");
	printf ("\t                 MODE: every XXms milliseconds, every YYgc collections, ondemand\n");
	printf ("\tsample[=TYPE]    use statistical sampling mode (by default cycles/1000)\n");
	printf ("\t                 TYPE: cycles,instr,cacherefs,cachemiss,branches,branchmiss\n");
	printf ("\t                 TYPE can be followed by /FREQUENCY\n");
	printf ("\ttime=fast        use a faster (but more inaccurate) timer\n");
	printf ("\tmaxframes=NUM    collect up to NUM stack frames\n");
	printf ("\tcalldepth=NUM    ignore method events for call chain depth bigger than NUM\n");
	printf ("\toutput=FILENAME  write the data to file FILENAME (-FILENAME to overwrite)\n");
	printf ("\toutput=|PROGRAM  write the data to the stdin of PROGRAM\n");
	printf ("\t                 %%t is subtituted with date and time, %%p with the pid\n");
	printf ("\treport           create a report instead of writing the raw data to a file\n");
	printf ("\tzip              compress the output data\n");
	printf ("\tport=PORTNUM     use PORTNUM for the listening command server\n");
	if (do_exit)
		exit (1);
}
