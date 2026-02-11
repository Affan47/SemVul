dump_packet_and_trunc(u_char *user, const struct pcap_pkthdr *h, const u_char *sp)
{
	struct dump_info *dump_info;

	++packets_captured;

	++infodelay;

	dump_info = (struct dump_info *)user;


	if (Gflag != 0) {

		time_t t;


		if ((t = time(NULL)) == (time_t)-1) {
			error("dump_and_trunc_packet: can't get current_time: %s",
			    pcap_strerror(errno));
		}


		if (t - Gflag_time >= Gflag) {

			Gflag_time = t;

			Gflag_count++;


			pcap_dump_close(dump_info->p);


			if (zflag != NULL)
				compress_savefile(dump_info->CurrentFileName);


			if (Cflag == 0 && Wflag > 0 && Gflag_count >= Wflag) {
				(void)fprintf(stderr, "Maximum file limit reached: %d\n",
				    Wflag);
				exit(0);

			}
			if (dump_info->CurrentFileName != NULL)
				free(dump_info->CurrentFileName);

			dump_info->CurrentFileName = (char *)malloc(NAME_MAX + 1);
			if (dump_info->CurrentFileName == NULL)
				error("dump_packet_and_trunc: malloc");


			if (Cflag != 0)
				MakeFilename(dump_info->CurrentFileName, dump_info->WFileName, 0,
				    WflagChars);
			else
				MakeFilename(dump_info->CurrentFileName, dump_info->WFileName, 0, 0);

			dump_info->p = pcap_dump_open(dump_info->pd, dump_info->CurrentFileName);
			if (dump_info->p == NULL)
				error("%s", pcap_geterr(pd));
		}
	}


	if (Cflag != 0 && pcap_dump_ftell(dump_info->p) > Cflag) {


		pcap_dump_close(dump_info->p);


		if (zflag != NULL)
			compress_savefile(dump_info->CurrentFileName);

		Cflag_count++;
		if (Wflag > 0) {
			if (Cflag_count >= Wflag)
				Cflag_count = 0;
		}
		if (dump_info->CurrentFileName != NULL)
			free(dump_info->CurrentFileName);
		dump_info->CurrentFileName = (char *)malloc(NAME_MAX + 1);
		if (dump_info->CurrentFileName == NULL)
			error("dump_packet_and_trunc: malloc");
		MakeFilename(dump_info->CurrentFileName, dump_info->WFileName, Cflag_count, WflagChars);
		dump_info->p = pcap_dump_open(dump_info->pd, dump_info->CurrentFileName);
		if (dump_info->p == NULL)
			error("%s", pcap_geterr(pd));
	}

	pcap_dump((u_char *)dump_info->p, h, sp);
#ifdef HAVE_PCAP_DUMP_FLUSH
	if (Uflag)
		pcap_dump_flush(dump_info->p);
#endif

	--infodelay;
	if (infoprint)
		info(0);
}
