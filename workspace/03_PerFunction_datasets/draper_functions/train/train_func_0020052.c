db_cmd_memdump(char *cmd, char *param1, char *param2, char *param3)
{
	unsigned long       addr1, addr2;

	if (db_ascii_to_hex(param1, &addr1) != -1 && db_ascii_to_hex(param2, &addr2) != -1 && addr1 < addr2 && addr1%4 == 0)
	{
		db_print_dump((const char *)addr1, (const char *)addr2);
		return 0;
	}

	db_incorect_format();
	return -1;
}
