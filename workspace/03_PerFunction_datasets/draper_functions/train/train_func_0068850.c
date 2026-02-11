ExplainQuery(ExplainStmt *stmt, ParamListInfo params, DestReceiver *dest)
{
	Query	   *query = stmt->query;
	TupOutputState *tstate;
	List	   *rewritten;
	ListCell   *l;


	query = copyObject(query);


	tstate = begin_tup_output_tupdesc(dest, ExplainResultDesc(stmt));

	if (query->commandType == CMD_UTILITY)
	{

		if (query->utilityStmt && IsA(query->utilityStmt, DeclareCursorStmt))
			ExplainOneQuery(query, stmt, params, tstate);
		else if (query->utilityStmt && IsA(query->utilityStmt, ExecuteStmt))
			ExplainExecuteQuery(stmt, params, tstate);
		else
			do_text_output_oneline(tstate, "Utility statements have no plan structure");
	}
	else
	{


		AcquireRewriteLocks(query);


		rewritten = QueryRewrite(query);

		if (rewritten == NIL)
		{

			do_text_output_oneline(tstate, "Query rewrites to nothing");
		}
		else
		{

			foreach(l, rewritten)
			{
				ExplainOneQuery(lfirst(l), stmt, params, tstate);

				if (lnext(l) != NULL)
					do_text_output_oneline(tstate, "");
			}
		}
	}

	end_tup_output(tstate);
}
