write_tree_source_node(FILE *f, struct node *tree, int level)
{
	struct property *prop;
	struct node *child;
	struct label *l;

	write_prefix(f, level);
	for_each_label(tree->labels, l)
		fprintf(f, "%s: ", l->label);
	if (tree->name && (*tree->name))
		fprintf(f, "%s {\n", tree->name);
	else
		fprintf(f, "/ {\n");

	for_each_property(tree, prop) {
		write_prefix(f, level+1);
		for_each_label(prop->labels, l)
			fprintf(f, "%s: ", l->label);
		fprintf(f, "%s", prop->name);
		write_propval(f, prop);
	}
	for_each_child(tree, child) {
		fprintf(f, "\n");
		write_tree_source_node(f, child, level+1);
	}
	write_prefix(f, level);
	fprintf(f, "};\n");
}
