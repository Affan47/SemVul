gel_lexer_parse(FILE *fp)
{
	YY_BUFFER_STATE buf;

	g_assert(fp_hash);

	buf = g_hash_table_lookup(fp_hash, fp);

	yy_switch_to_buffer(buf);
	yyparse();
}
