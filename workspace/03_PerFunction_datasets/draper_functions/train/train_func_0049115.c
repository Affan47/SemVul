main(int argc, char **argv)
{
	struct options opt;

	if (parse_options(argc, argv, &opt) < 0)
		return -1;

	srandom(get_seed());

	return opt.command->func(&opt);
}
