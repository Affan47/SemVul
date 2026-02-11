parse_opt(int k, char *optarg, struct argp_state *state)
{
	struct arguments *args = state->input;
	switch (k) {
	case 'I':
		args->input_format = parse_format(optarg);
		break;
	case 'O':
		args->output_format = parse_format(optarg);
		break;
	case 's':
		args->delsys = parse_delsys(optarg);
		break;
	default:
		return ARGP_ERR_UNKNOWN;
	};
	return 0;
}
