plpgsql_stmt_typename(PLpgSQL_stmt *stmt)
{
	switch (stmt->cmd_type)
	{
		case PLPGSQL_STMT_BLOCK:
			return "block variables initialization";
		case PLPGSQL_STMT_ASSIGN:
			return "assignment";
		case PLPGSQL_STMT_IF:
			return "if";
		case PLPGSQL_STMT_LOOP:
			return "loop";
		case PLPGSQL_STMT_WHILE:
			return "while";
		case PLPGSQL_STMT_FORI:
			return "for with integer loopvar";
		case PLPGSQL_STMT_FORS:
			return "for over select rows";
		case PLPGSQL_STMT_EXIT:
			return "exit";
		case PLPGSQL_STMT_RETURN:
			return "return";
		case PLPGSQL_STMT_RETURN_NEXT:
			return "return next";
		case PLPGSQL_STMT_RAISE:
			return "raise";
		case PLPGSQL_STMT_EXECSQL:
			return "SQL statement";
		case PLPGSQL_STMT_DYNEXECUTE:
			return "execute statement";
		case PLPGSQL_STMT_DYNFORS:
			return "for over execute statement";
		case PLPGSQL_STMT_GETDIAG:
			return "get diagnostics";
		case PLPGSQL_STMT_OPEN:
			return "open";
		case PLPGSQL_STMT_FETCH:
			return "fetch";
		case PLPGSQL_STMT_CLOSE:
			return "close";
		case PLPGSQL_STMT_PERFORM:
			return "perform";
	}

	return "unknown";
}
