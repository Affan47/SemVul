kdb_ss(int argc, const char **argv)
{
	if (argc != 0)
		return KDB_ARGCOUNT;


	KDB_STATE_SET(DOING_SS);
	return KDB_CMD_SS;
}
