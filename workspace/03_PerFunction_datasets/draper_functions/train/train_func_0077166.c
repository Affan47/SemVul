main(int argc, char **argv)
{
	if (argc != 1)
		usage(patch_id_usage);

	generate_id_list();
	return 0;
}
