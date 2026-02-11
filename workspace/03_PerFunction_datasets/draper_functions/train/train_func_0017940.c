rtl_evm_db_to_percentage(char value)
{
	char ret_val = clamp(-value, 0, 33) * 3;

	if (ret_val == 99)
		ret_val = 100;

	return ret_val;
}
