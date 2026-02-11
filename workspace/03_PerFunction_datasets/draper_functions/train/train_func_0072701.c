dump_raise(PLpgSQL_stmt_raise *stmt)
{
	ListCell   *lc;
	int			i = 0;

	dump_ind();
	printf("RAISE level=%d", stmt->elog_level);
	if (stmt->condname)
		printf(" condname='%s'", stmt->condname);
	if (stmt->message)
		printf(" message='%s'", stmt->message);
	printf("\n");
	dump_indent += 2;
	foreach(lc, stmt->params)
	{
		dump_ind();
		printf("    parameter %d: ", i++);
		dump_expr((PLpgSQL_expr *) lfirst(lc));
		printf("\n");
	}
	if (stmt->options)
	{
		dump_ind();
		printf("    USING\n");
		dump_indent += 2;
		foreach(lc, stmt->options)
		{
			PLpgSQL_raise_option *opt = (PLpgSQL_raise_option *) lfirst(lc);

			dump_ind();
			switch (opt->opt_type)
			{
				case PLPGSQL_RAISEOPTION_ERRCODE:
					printf("    ERRCODE = ");
					break;
				case PLPGSQL_RAISEOPTION_MESSAGE:
					printf("    MESSAGE = ");
					break;
				case PLPGSQL_RAISEOPTION_DETAIL:
					printf("    DETAIL = ");
					break;
				case PLPGSQL_RAISEOPTION_HINT:
					printf("    HINT = ");
					break;
			}
			dump_expr(opt->expr);
			printf("\n");
		}
		dump_indent -= 2;
	}
	dump_indent -= 2;
}
