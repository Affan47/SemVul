mono_test_Winx64_struct5_ret_managed (managed_struct5_ret_delegate func)
{
	winx64_struct5 ret;

	ret = func ();

	if (ret.a != 0x12)
		return 1;
	if (ret.b != 0x34)
		return 2;
	if (ret.c != 0x56)
		return 3;

	return 0;
}
