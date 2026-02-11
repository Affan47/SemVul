print_text_helper(dns_rbtnode_t *root, dns_rbtnode_t *parent,
		  int depth, const char *direction,
		  void (*data_printer)(FILE *, void *), FILE *f)
{
	dns_rbt_indent(f, depth);

	if (root != NULL) {
		printnodename(root, ISC_TRUE, f);
		fprintf(f, " (%s, %s", direction,
			IS_RED(root) ? "RED" : "BLACK");

		if ((! IS_ROOT(root) && PARENT(root) != parent) ||
		    (  IS_ROOT(root) && depth > 0 &&
		       DOWN(PARENT(root)) != root)) {

			fprintf(f, " (BAD parent pointer! -> ");
			if (PARENT(root) != NULL)
				printnodename(PARENT(root), ISC_TRUE, f);
			else
				fprintf(f, "NULL");
			fprintf(f, ")");
		}

		fprintf(f, ")");

		if (root->data != NULL && data_printer != NULL) {
			fprintf(f, " data@%p: ", root->data);
			data_printer(f, root->data);
		}
		fprintf(f, "\n");

		depth++;

		if (IS_RED(root) && IS_RED(LEFT(root)))
			fprintf(f, "** Red/Red color violation on left\n");
		print_text_helper(LEFT(root), root, depth, "left",
					  data_printer, f);

		if (IS_RED(root) && IS_RED(RIGHT(root)))
			fprintf(f, "** Red/Red color violation on right\n");
		print_text_helper(RIGHT(root), root, depth, "right",
					  data_printer, f);

		print_text_helper(DOWN(root), NULL, depth, "down",
					  data_printer, f);
	} else {
		fprintf(f, "NULL (%s)\n", direction);
	}
}
