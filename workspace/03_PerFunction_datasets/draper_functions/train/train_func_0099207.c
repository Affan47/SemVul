get_pindicator_str(char *buf, int max_len)
{
	Address *addr;
	if (analy && getCurrentAddress(&addr)) {
		std::auto_ptr<Address> blub(addr);
		FileOfs o;
		global_analyser_address_string_format = ADDRESS_STRING_FORMAT_COMPACT;
		if (get_current_offset(&o)) {
			return ht_snprintf(buf, max_len, " %y/@%08qx%s ", addr, o, (analy->isDirty())?" dirty":"");
		} else {
			return ht_snprintf(buf, max_len, " %y%s ", addr, (analy->isDirty())?" dirty":"");
		}
	} else {
		return ht_snprintf(buf, max_len, " ? ");
	}
}
