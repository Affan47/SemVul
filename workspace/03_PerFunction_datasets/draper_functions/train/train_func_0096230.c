xml_write_tree_recursive(GNode *node, FILE *fp)
{
	gint i, depth;
	XMLTag *tag;
	GList *cur;

	cm_return_val_if_fail(node != NULL, -1);
	cm_return_val_if_fail(fp != NULL, -1);

	depth = g_node_depth(node) - 1;
	for (i = 0; i < depth; i++)
		TRY(fputs("    ", fp) != EOF);

	tag = ((XMLNode *) node->data)->tag;

	TRY(fprintf(fp, "<%s", tag->tag) > 0);

	for (cur = tag->attr; cur != NULL; cur = g_list_next(cur)) {
		XMLAttr *attr = (XMLAttr *) cur->data;

		TRY(fprintf(fp, " %s=\"", attr->name) > 0);
		TRY(xml_file_put_escape_str(fp, attr->value) == 0);
		TRY(fputs("\"", fp) != EOF);

	}

	if (node->children) {
		GNode *child;
		TRY(fputs(">\n", fp) != EOF);

		child = node->children;
		while (child) {
			GNode *cur;

			cur = child;
			child = cur->next;
			TRY(xml_write_tree_recursive(cur, fp) == 0);
		}

		for (i = 0; i < depth; i++)
			TRY(fputs("    ", fp) != EOF);
		TRY(fprintf(fp, "</%s>\n", tag->tag) > 0);
	} else
		TRY(fputs(" />\n", fp) != EOF);

	return 0;
}
