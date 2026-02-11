debugstate(struct io_data *io_data, __maybe_unused SOCKETTYPE c, char *param, bool isjson, __maybe_unused char group)
{
	struct api_data *root = NULL;
	bool io_open;

	if (param == NULL)
		param = (char *)BLANK;
	else
		*param = tolower(*param);

	switch(*param) {
	case 's':
		opt_realquiet = true;
		break;
	case 'q':
		opt_quiet ^= true;
		break;
	case 'v':
		opt_log_output ^= true;
		if (opt_log_output)
			opt_quiet = false;
		break;
	case 'd':
		opt_debug ^= true;
		opt_log_output = opt_debug;
		if (opt_debug)
			opt_quiet = false;
		break;
	case 'r':
		opt_protocol ^= true;
		if (opt_protocol)
			opt_quiet = false;
		break;
	case 'p':
		want_per_device_stats ^= true;
		opt_log_output = want_per_device_stats;
		break;
	case 'n':
		opt_log_output = false;
		opt_debug = false;
		opt_quiet = false;
		opt_protocol = false;
		want_per_device_stats = false;
		opt_worktime = false;
		break;
	case 'w':
		opt_worktime ^= true;
		break;
#ifdef _MEMORY_DEBUG
	case 'y':
		cgmemspeedup();
		break;
	case 'z':
		cgmemrpt();
		break;
#endif
	default:

		break;
	}

	message(io_data, MSG_DEBUGSET, 0, NULL, isjson);
	io_open = io_add(io_data, isjson ? COMSTR JSON_DEBUGSET : _DEBUGSET COMSTR);

	root = api_add_bool(root, "Silent", &opt_realquiet, false);
	root = api_add_bool(root, "Quiet", &opt_quiet, false);
	root = api_add_bool(root, "Verbose", &opt_log_output, false);
	root = api_add_bool(root, "Debug", &opt_debug, false);
	root = api_add_bool(root, "RPCProto", &opt_protocol, false);
	root = api_add_bool(root, "PerDevice", &want_per_device_stats, false);
	root = api_add_bool(root, "WorkTime", &opt_worktime, false);

	root = print_data(io_data, root, isjson, false);
	if (isjson && io_open)
		io_close(io_data);
}
