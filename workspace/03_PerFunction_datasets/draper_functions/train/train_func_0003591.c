dump_raise(PLpgSQL_stmt_raise *stmt)
{
	ListCell   *lc;
	int			i = 0;

	dump_ind();
	printf("RAISE '%s'\n", stmt->message);
	dump_indent += 2;
	foreach(lc, stmt->params)
	{
		dump_ind();
		printf("    parameter %d: ", i++);
		dump_expr((PLpgSQL_expr *) lfirst(lc));
		printf("\n");
	}
	dump_indent -= 2;
}
