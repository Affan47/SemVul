act_keyctl_newring(int argc, char *argv[])
{
	key_serial_t dest;
	int ret;

	if (argc != 3)
		format();

	dest = get_key_id(argv[2]);

	ret = add_key("keyring", argv[1], NULL, 0, dest);
	if (ret < 0)
		error("add_key");

	printf("%d\n", ret);
	return 0;

}
