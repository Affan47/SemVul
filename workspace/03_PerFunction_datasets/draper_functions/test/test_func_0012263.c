coff_rva_to_ofs(coff_section_headers *section_headers, RVA rva, FileOfs *ofs)
{
	COFF_SECTION_HEADER *s = section_headers->sections;
	for (uint i = 0; i < section_headers->section_count; i++) {
		if (s->data_offset && rva >= s->data_address
		&& rva < s->data_address+s->data_size) {
			*ofs = rva-s->data_address + s->data_offset + section_headers->hdr_ofs;
			return true;
		}
		s++;
	}
	return false;
}
