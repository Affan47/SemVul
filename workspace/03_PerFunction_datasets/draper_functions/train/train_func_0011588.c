nvpair_print_html_with_link(struct nvpair *n, FILE * s, struct nvpair_header *h, const char *linkname, const char *linktext)
{
	fprintf(s, "<tr bgcolor=%s>\n", color_counter % 2 ? COLOR_ONE : COLOR_TWO);
	color_counter++;
	while(h->name) {
		const char *text = nvpair_lookup_string(n, h->name);
		if(!text)
			text = "???";
		fprintf(s, "<td align=%s>", align_string(h));
		if(h->mode == NVPAIR_MODE_URL) {
			fprintf(s, "<a href=%s>%s</a>\n", text, text);
		} else if(h->mode == NVPAIR_MODE_METRIC) {
			char line[1024];
			string_metric(atof(text), -1, line);
			fprintf(s, "%sB\n", line);
		} else {
			if(linkname && !strcmp(linkname, h->name)) {
				fprintf(s, "<a href=%s>%s</a>\n", linktext, text);
			} else {
				fprintf(s, "%s\n", text);
			}
		}
		h++;
	}
}
