processIRFList(int argc, char** argv)
{
	irf_list.clear();
	while (optind < argc && *(argv[optind]) != '-') {
		irf_list.push_back(argv[optind]);
		optind++;
	}
}
