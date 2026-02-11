mono_test_Winx64_struct2_in (winx64_struct2 var)
{
	if (var.a != 4)
		return 1;
	if (var.b != 5)
		return 2;
	return 0;
}
