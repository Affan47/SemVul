swan_ts_detect_clients_main(int argc, char *argv[])
{
	u16 start;
	u16 end;

	start = argc > 1 ? text2value_unsigned(argv[1], NULL, 10) : 1;
	end = argc > 2 ? text2value_unsigned(argv[2], NULL, 10) : 0x7F;

	return swan_ts_detect_clients(argc > 3 ? argv[3] : NULL, start, end);
}
