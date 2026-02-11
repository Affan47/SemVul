invalid_header(struct hfi1_devdata *dd, const char *what,
			  u32 actual, u32 expected)
{
	if (actual == expected)
		return 0;

	dd_dev_err(dd,
		"invalid firmware header field %s: expected 0x%x, actual 0x%x\n",
		what, expected, actual);
	return 1;
}
