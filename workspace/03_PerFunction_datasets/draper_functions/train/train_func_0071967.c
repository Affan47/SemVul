is_string_constant(const char* str)
{
	return str[0] == '.' || str[0] == '-' || (str[0] >= '0' && str[0] <= '9');
}
