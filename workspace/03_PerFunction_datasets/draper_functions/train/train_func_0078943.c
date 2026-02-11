free_block(PLpgSQL_stmt_block *block)
{
	free_stmts(block->body);
	if (block->exceptions)
	{
		ListCell   *e;

		foreach(e, block->exceptions->exc_list)
		{
			PLpgSQL_exception *exc = (PLpgSQL_exception *) lfirst(e);

			free_stmts(exc->action);
		}
	}
}
