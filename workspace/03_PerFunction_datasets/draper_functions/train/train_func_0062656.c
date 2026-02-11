process_opt(void *context, int ch, char *optarg)
{
	switch (ch) {
	case 'c':
		cckey = (uint64_t) strtoull(optarg, 0, 0);
		break;
	default:
		return -1;
	}
	return 0;
}
