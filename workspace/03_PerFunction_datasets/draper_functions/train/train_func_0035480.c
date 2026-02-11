run_tests()
{
	wstring vert_sep = wstring(L"+-") + wstring(DESC_LENGTH, L'-') + wstring(L"-+--------+\r\n");

	print_out(vert_sep.c_str());

	wstring header = wstring(L"| Test case") + wstring(DESC_LENGTH - 9, L' ') + wstring(L" | Result |\r\n");
	print_out(header.c_str());

	print_out(vert_sep.c_str());

	run_test_type(true);
	run_test_type(false);


	double decimal = 40.9358215191158457340974;
	JSONValue *json_value = JSON::Parse("40.9358215191158457340974");
	wstring test_output = wstring(L"| Very precise decimal number") + wstring(DESC_LENGTH - 27, L' ') + wstring(L" | ");
	if (json_value && json_value->IsNumber() && json_value->AsNumber() == decimal)
	{
		test_output += wstring(L"passed |\r\n");
		delete json_value;
	}
	else
	{
		test_output += wstring(L"failed |\r\n");
	}
	print_out(test_output.c_str());


	decimal = 1.00034985734000;
	json_value = JSON::Parse("1.00034985734000");
	test_output = wstring(L"| Decimal number with leading zeros") + wstring(DESC_LENGTH - 33, L' ') + wstring(L" | ");
	if (json_value && json_value->IsNumber() && json_value->AsNumber() == decimal)
	{
		test_output += wstring(L"passed |\r\n");
	}
	else
	{
		test_output += wstring(L"failed |\r\n");
	}
	print_out(test_output.c_str());

	print_out(vert_sep.c_str());
}
