insert_arg_rule(char *arg, char *tag)
{
int	lineno = rescan_lineno;
char	*code = compile_arg(&arg, tag);
int	rule = lookup_arg_cache(code);
FILE	*f = action_file;

    if (rule<0) {
	rule = nrules;
	insert_arg_cache(code, rule);
	fprintf(f, "case %d:\n", rule - 2);
	if (!lflag)
	    fprintf(f, line_format, lineno, (inc_file?inc_file_name:input_file_name));
	fprintf(f, "%s;\n", code);
	fprintf(f, "break;\n");
	insert_empty_rule();
	plhs[rule]->tag = tag;
	plhs[rule]->class = ARGUMENT; }
    else {
	if (++nitems > maxitems)
	    expand_items();
	pitem[nitems-1] = plhs[rule];
	free(code); }
    return arg+1;
}
