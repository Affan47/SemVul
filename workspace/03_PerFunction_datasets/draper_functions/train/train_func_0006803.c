print_supported_files(void)
{
	int i;

	print_banner();
	printf("\nExtracting firmware is possible "
	       "from these binary driver files.\n"
	       "Please read http://linuxwireless.org/en/users/Drivers/b43#devicefirmware\n\n");
	printf("<driver>\t"
	       "<filename>\t\t"
	       "<microcode>\t"
	       "<MD5 checksum>\n\n");

	for (i = 0; i < ARRAY_SIZE(files); i++)
		if (file_ok(&files[i]) && !(files[i].flags & FW_FLAG_V4))
			print_file(&files[i]);
	for (i = 0; i < ARRAY_SIZE(files); i++)
		if (file_ok(&files[i]) && files[i].flags & FW_FLAG_V4)
			print_file(&files[i]);
	printf("\n");
}
