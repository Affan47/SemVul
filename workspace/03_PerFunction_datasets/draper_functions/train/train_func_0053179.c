validAddress(Address *Addr, tsectype action)
{
	pef_section_headers *sections=&pef_shared->sheaders;
	int sec;
	PEFAddress ea;
	if (!convertAddressToPEFAddress(Addr, &ea)) return false;
	if (!pef_addr_to_section(sections, ea, &sec)) return false;
	PEF_SECTION_HEADER *s = sections->sheaders + sec;
	switch (action) {
		case scvalid:
			return true;
		case scread:
			return true;
		case scwrite:
		case screadwrite:
			return (s->sectionKind == 1) ||
				(s->sectionKind == 2) ||
				(s->sectionKind == 6);
		case sccode:
			return (s->sectionKind == 0);
		case scinitialized:
			return (s->sectionKind == 0) ||
				(s->sectionKind == 1) ||
				(s->sectionKind == 3) ||
				(s->sectionKind == 6)	;
	}
	return false;
}
