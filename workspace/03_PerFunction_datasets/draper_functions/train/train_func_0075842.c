aparam(char ** xml, unsigned * size, const char ** param) {
	if(xml && size) {
		unsigned n;

		append(xml, size, "\t\t<param><value><array><data>");

		for(n = 0; param && param[n] != NULL; ++n) {
			char * encoded = xmlize(param[n]);
			append(xml, size, "<value><string>");
			append(xml, size, encoded);
			append(xml, size, "</string></value>");
			free(encoded);
		}

		append(xml, size, "</data></array></value></param>\n");
	}
}
