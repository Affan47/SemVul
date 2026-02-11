main(int argc, char **argv)
{
	struct ctf_scanner *scanner;
	struct ctf_trace *trace;
	int ret = 0;

	babeltrace_debug = 1;
	babeltrace_verbose = 1;
	scanner = ctf_scanner_alloc();
	if (!scanner) {
		fprintf(stderr, "Error allocating scanner\n");
		return -ENOMEM;
	}
	ret = ctf_scanner_append_ast(scanner, stdin);
	if (ret) {
		fprintf(stderr, "Error creating AST\n");
		goto end;
	}

	ret = ctf_visitor_print_xml(stderr, 0, &scanner->ast->root);
	if (ret) {
		fprintf(stderr, "Error visiting AST for XML output\n");
		goto end;
	}

	ret = ctf_visitor_semantic_check(stderr, 0, &scanner->ast->root);
	if (ret) {
		fprintf(stderr, "Error in CTF semantic validation %d\n", ret);
		goto end;
	}
	trace = malloc(sizeof(*trace));
	memset(trace, 0, sizeof(*trace));
	ret = ctf_visitor_construct_metadata(stderr, 0, &scanner->ast->root,
			trace, BYTE_ORDER);
	if (ret) {
		fprintf(stderr, "Error in CTF metadata constructor %d\n", ret);
		goto free_trace;
	}
free_trace:
	free(trace);
end:
	ctf_scanner_free(scanner);
	return ret;
}
