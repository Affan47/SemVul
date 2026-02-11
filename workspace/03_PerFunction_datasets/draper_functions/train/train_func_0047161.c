aic_print_reg_dump_start(FILE *dfile, symbol_node_t *regnode)
{
	if (dfile == NULL)
		return;

	fprintf(dfile,
"static %sreg_parse_entry_t %s_parse_table[] = {\n",
		prefix,
		regnode->symbol->name);
}
