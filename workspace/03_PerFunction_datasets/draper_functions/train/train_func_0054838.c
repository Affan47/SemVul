mono_test_Winx64_struct5_in (winx64_struct5 var)
{
	if (var.a != 4)
		return 1;
	if (var.b != 5)
		return 2;
	if (var.c != 6)
		return 3;
	return 0;
}
