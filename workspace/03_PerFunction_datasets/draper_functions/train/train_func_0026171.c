collect_sections (MonoImageWriter *acfg, ElfSectHeader *sheaders, BinSection **out, int num)
{
	int i, j, maxs, num_sections;
	BinSection *sect;

	num_sections = 0;
	maxs = 0;
	for (sect = acfg->sections; sect; sect = sect->next) {
		if (sect->subsection == 0) {
			out [num_sections++] = sect;
			g_assert (num_sections < num);
		}
		maxs = MAX (maxs, sect->subsection);
	}
	for (i = 0; i < num_sections; i++) {
		for (j = 1; j <= maxs; ++j) {
			for (sect = acfg->sections; sect; sect = sect->next) {
				if (sect->subsection == j && strcmp (out [i]->name, sect->name) == 0) {
					append_subsection (acfg, sheaders, out [i], sect);
				}
			}
		}
	}
	return num_sections;
}
