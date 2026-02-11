coff_rva_is_physical(coff_section_headers *section_headers, RVA rva)
{
	COFF_SECTION_HEADER *s=section_headers->sections;
	for (uint i=0; i<section_headers->section_count; i++) {
		if (s->data_offset && (rva >= s->data_address) &&
		(rva < s->data_address+s->data_size)) {
			return true;
		}
		s++;
	}
	return false;
}
