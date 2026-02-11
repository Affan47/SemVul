export_binary (int argc, char **argv, void *data)
{
	Node *node = (Node *) data;
	char *filename = argc>=2?argv[1]:"";
	FILE *file;

	if (!strcmp (filename, "-"))
		file = stdout;
	else
		file = fopen (filename, "w");

	if (!file) {
		cli_outfunf ("binary export, unable to open \"%s\"", filename);
		return node;
	}

	fwrite (&hnb_binary_header, 4, 1, file);
	fwrite (&hnb_binary_version, 4, 1, file);

	binary_export_nodes (file, node, 0);

	cli_outfunf ("binary export, wrote data to \"%s\"", filename);

	return node;
}
