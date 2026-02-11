dump_fetch(PLpgSQL_stmt_fetch *stmt)
{
	dump_ind();
	printf("FETCH curvar=%d\n", stmt->curvar);

	dump_indent += 2;
	if (stmt->rec != NULL)
	{
		dump_ind();
		printf("    target = %d %s\n", stmt->rec->recno, stmt->rec->refname);
	}
	if (stmt->row != NULL)
	{
		dump_ind();
		printf("    target = %d %s\n", stmt->row->rowno, stmt->row->refname);
	}
	dump_indent -= 2;

}
