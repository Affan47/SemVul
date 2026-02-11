host_is_big_endian(void)
{
	uint32_t tmp_u32;
	char tmp_str[sizeof(uint32_t)];

	tmp_u32 = 0x00000001;
	memcpy(tmp_str, (char *)&tmp_u32, sizeof(uint32_t));
	if (tmp_str[0] == 0x01)
		return 0;


	else
		return 1;


}
