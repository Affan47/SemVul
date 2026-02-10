ctf_visitor_print_type_specifier_list(FILE *fd, int depth, struct ctf_node *node)
{
	struct ctf_node *iter;
	int ret;

	print_tabs(fd, depth);
	fprintf(fd, "<type_specifier_list>\n");
	bt_list_for_each_entry(iter, &node->u.type_specifier_list.head, siblings) {
		ret = ctf_visitor_print_xml(fd, depth + 1, iter);
		if (ret)
			return ret;
	}
	print_tabs(fd, depth);
	fprintf(fd, "</type_specifier_list>\n");
	return 0;
}
