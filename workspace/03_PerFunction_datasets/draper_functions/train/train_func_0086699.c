pef_addr_to_section(pef_section_headers *section_headers, PEFAddress addr, int *section)
{
	PEF_SECTION_HEADER *s = section_headers->sheaders;
	for (uint i = 0; i < section_headers->count; i++) {
		if ((pef_valid_section(s)) &&
		(addr.a32 >= s->defaultAddress) && (addr.a32 < s->defaultAddress + s->totalSize)) {
			*section = i;
			return true;
		}
		s++;
	}
	return false;
}
