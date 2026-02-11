probe_cmd_generic_timed(comedi_t *it,int s,int n_channels,int freq_for_generic_timed)
{
	comedi_cmd cmd;
	char buf[100];

	printf("  command structure filled with probe_cmd_generic_timed for %d channels:\n",
	       n_channels);
	if(comedi_get_cmd_generic_timed(it, s, &cmd, n_channels, 1E9/freq_for_generic_timed)<0){
		printf("    not supported\n");
	}else{
		printf("    start: %s %d\n",
			cmd_src(cmd.start_src,buf),cmd.start_arg);
		printf("    scan_begin: %s %d\n",
			cmd_src(cmd.scan_begin_src,buf),cmd.scan_begin_arg);
		if (verbose) {
			if ((cmd.scan_begin_src == TRIG_TIMER)&&(cmd.scan_begin_arg)) {
				printf("      scan_begin_src = TRIG_TIMER:\n"
				       "      The sampling rate is defined per scan\n"
				       "      meaning all channels are sampled at\n"
				       "      the same time. The maximum sampling rate is f=%d Hz\n",
				       (int)(1E9/cmd.scan_begin_arg));}
		}
		printf("    convert: %s %d\n",
			cmd_src(cmd.convert_src,buf),cmd.convert_arg);
		if (verbose) {
			if ((cmd.convert_src == TRIG_TIMER)&&(cmd.convert_arg)) {
				printf("      convert_src = TRIG_TIMER\n"
				       "      The sampling rate is defined per channel\n"
				       "      meaning that a multiplexer is being switched from\n"
				       "      channel to channel at a maximum rate of %d Hz.\n"
				       "      The overall sampling rate needs to be divided\n"
				       "      by the number of channels and results in f=%d Hz.\n",
				       (int)(1E9/cmd.convert_arg),
				       (int)(1E9/cmd.convert_arg/n_channels));
			}
		}
		printf("    scan_end: %s %d\n",
			cmd_src(cmd.scan_end_src,buf),cmd.scan_end_arg);
		printf("    stop: %s %d\n",
			cmd_src(cmd.stop_src,buf),cmd.stop_arg);
	}
}
