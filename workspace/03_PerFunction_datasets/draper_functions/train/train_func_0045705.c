assembly(const char *file)
{
	asm_target = sflag ? SYM : rflag ? REF : DEF;

	if (linetable_open(file) == -1)
		die("'%s' cannot open.", file);
	asm_input_file = file;

	asm_symtable = strbuf_open(0);
	asm_initscan();

	asm_parse();

	strbuf_close(asm_symtable);
	linetable_close();
}
