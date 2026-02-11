c_font_weight(string& value)
{
	string important = "";
	if(is_important(value))
	{
		important = "!important";
		value = gvw_important(value);
	}
	if(value == "bold")
	{
		value = "700"+important;
		return 700;
	}
	else if(value == "normal")
	{
		value = "400"+important;
		return 400;
	}
	return 0;
}
