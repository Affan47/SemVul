tuner_cmd(int ch, char *optarg)
{
	switch (ch) {
	case OptSetFreq:
		freq = strtod(optarg, NULL);
		break;
	case OptSetTuner:
		if (!strcmp(optarg, "stereo"))
			mode = V4L2_TUNER_MODE_STEREO;
		else if (!strcmp(optarg, "lang1"))
			mode = V4L2_TUNER_MODE_LANG1;
		else if (!strcmp(optarg, "lang2"))
			mode = V4L2_TUNER_MODE_LANG2;
		else if (!strcmp(optarg, "bilingual"))
			mode = V4L2_TUNER_MODE_LANG1_LANG2;
		else if (!strcmp(optarg, "mono"))
			mode = V4L2_TUNER_MODE_MONO;
		else {
			fprintf(stderr, "Unknown audio mode\n");
			tuner_usage();
			exit(1);
		}
		break;
	case OptSetModulator:
		txsubchans = strtol(optarg, 0L, 0);
		if (!strcmp(optarg, "stereo"))
			txsubchans = V4L2_TUNER_SUB_STEREO;
		else if (!strcmp(optarg, "stereo-sap"))
			txsubchans = V4L2_TUNER_SUB_STEREO | V4L2_TUNER_SUB_SAP;
		else if (!strcmp(optarg, "bilingual"))
			txsubchans = V4L2_TUNER_SUB_LANG1;
		else if (!strcmp(optarg, "mono"))
			txsubchans = V4L2_TUNER_SUB_MONO;
		else if (!strcmp(optarg, "mono-sap"))
			txsubchans = V4L2_TUNER_SUB_MONO | V4L2_TUNER_SUB_SAP;
		else if (!strcmp(optarg, "stereo-rds"))
			txsubchans = V4L2_TUNER_SUB_STEREO | V4L2_TUNER_SUB_RDS;
		else if (!strcmp(optarg, "mono-rds"))
			txsubchans = V4L2_TUNER_SUB_MONO | V4L2_TUNER_SUB_RDS;
		else {
			fprintf(stderr, "Unknown txsubchans value\n");
			tuner_usage();
			exit(1);
		}
		break;
	case OptFreqSeek:
		parse_freq_seek(optarg, freq_seek);
		break;
	case OptTunerIndex:
		tuner_index = strtoul(optarg, NULL, 0);
		break;
	}
}
