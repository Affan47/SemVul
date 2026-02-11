write_bool8(bool data)
{
	bool final = data;
	if (little_endian_mode)
	{
		SWAP_IF_BIG(final);
	}
	else
	{
		SWAP_IF_LITTLE(final);
	}
	write(&final, sizeof(bool));
}
