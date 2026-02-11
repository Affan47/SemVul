kgdbts_put_char(u8 chr)
{
	if (ts.run_test)
		ts.run_test(0, chr);
}
