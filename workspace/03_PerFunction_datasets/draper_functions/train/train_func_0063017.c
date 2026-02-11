print_table(proplist_t *props) {
	char *name = props->val;
	int a_line_precedeth_this = 0;

	printf("\t\"%s\" [shape=record label=\"{", name);
	print_xml_escaped(name);
	for (props = props->next; props; props = props->next) {
		if (props->line) {
			printf("|");
			a_line_precedeth_this = 1;
		} else {
			printf("%s%s", a_line_precedeth_this ? "" : "\\n", props->val);
			a_line_precedeth_this = 0;
		}
	}
	printf("}\"];\n");
}
