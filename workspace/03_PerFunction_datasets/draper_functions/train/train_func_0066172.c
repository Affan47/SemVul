local_comp_destroy(unsigned int comp_id)
{
	unsigned int ci;
	unsigned int i;

	for (ci = 0; ; ci++) {
		if (ci == sizeof(comp) / sizeof(comp[0])) {

			assert(0);
			return;
		}
		if (comp[ci].id == comp_id
		 && comp[ci].type
		 && comp[ci].name) {

			break;
		}
	}

	for (i = 0; ; i++) {
		if (i == sizeof(comp_type) / sizeof(comp_type[0])) {
			fprintf(stderr, "%s\n", comp[ci].type);
			assert(0);
		}
		if (strcasecmp(comp[ci].type, comp_type[i].type) == 0) {
			if (comp_type[i].destroy) {
				comp_type[i].destroy(comp[ci].ptr);
			}
			if (comp_type[i].gui_destroy) {
				comp_type[i].gui_destroy(comp[ci].gui_ptr);
			}
			if (comp_type[i].aui_destroy) {
				comp_type[i].aui_destroy(comp[ci].aui_ptr);
			}
			break;
		}
	}

	free(comp[ci].type);
	comp[ci].type = NULL;

	free(comp[ci].name);
	comp[ci].name = NULL;
}
