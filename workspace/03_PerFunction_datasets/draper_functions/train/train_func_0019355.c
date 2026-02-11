act_keyctl_instantiate(int argc, char *argv[])
{
	key_serial_t key, dest;

	if (argc != 4)
		format();

	key = get_key_id(argv[1]);
	dest = get_key_id(argv[3]);

	if (keyctl_instantiate(key, argv[2], strlen(argv[2]), dest) < 0)
		error("keyctl_instantiate");

	return 0;

}
