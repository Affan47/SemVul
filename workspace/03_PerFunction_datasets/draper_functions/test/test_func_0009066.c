main(int argc, char *argv[])
{
	int ret = main_internal(argc, argv);
	if (ret <= 0) {
		return 1;
	}
	return 0;
}
