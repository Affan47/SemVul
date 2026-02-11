string_func(uint32 ofs, void *context)
{
	char str[1024];
	static char str2[1024];
	ht_pe_shared_data *pe = (ht_pe_shared_data*)context;
	if (ofs < pe->il->string_pool_size) {
		uint32 length;
		uint32 o = ILunpackDword(length, (byte*)&pe->il->string_pool[ofs], 10);
		wide_char_to_multi_byte(str, (byte*)&pe->il->string_pool[ofs+o], length/2+1);
		escape_special_str(str2, sizeof str2, str, "\"");
		return str2;
	} else {
		return NULL;
	}
}
