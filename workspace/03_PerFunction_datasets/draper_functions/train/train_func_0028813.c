bin_writer_emit_section_change (MonoImageWriter *acfg, const char *section_name, int subsection_index)
{
	BinSection *section;

	if (acfg->cur_section && acfg->cur_section->subsection == subsection_index
			&& strcmp (acfg->cur_section->name, section_name) == 0)
		return;
	for (section = acfg->sections; section; section = section->next) {
		if (section->subsection == subsection_index && strcmp (section->name, section_name) == 0) {
			acfg->cur_section = section;
			return;
		}
	}
	if (!section) {
		section = g_new0 (BinSection, 1);
		section->name = g_strdup (section_name);
		section->subsection = subsection_index;
		section->next = acfg->sections;
		acfg->sections = section;
		acfg->cur_section = section;
	}
}
