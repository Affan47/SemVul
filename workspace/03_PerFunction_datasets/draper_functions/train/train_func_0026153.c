get_with_clause(Query *query, deparse_context *context)
{
	StringInfo	buf = context->buf;
	const char *sep;
	ListCell   *l;

	if (query->cteList == NIL)
		return;

	if (PRETTY_INDENT(context))
	{
		context->indentLevel += PRETTYINDENT_STD;
		appendStringInfoChar(buf, ' ');
	}

	if (query->hasRecursive)
		sep = "WITH RECURSIVE ";
	else
		sep = "WITH ";
	foreach(l, query->cteList)
	{
		CommonTableExpr *cte = (CommonTableExpr *) lfirst(l);

		appendStringInfoString(buf, sep);
		appendStringInfoString(buf, quote_identifier(cte->ctename));
		if (cte->aliascolnames)
		{
			bool		first = true;
			ListCell   *col;

			appendStringInfoChar(buf, '(');
			foreach(col, cte->aliascolnames)
			{
				if (first)
					first = false;
				else
					appendStringInfoString(buf, ", ");
				appendStringInfoString(buf,
									   quote_identifier(strVal(lfirst(col))));
			}
			appendStringInfoChar(buf, ')');
		}
		appendStringInfoString(buf, " AS (");
		if (PRETTY_INDENT(context))
			appendContextKeyword(context, "", 0, 0, 0);
		get_query_def((Query *) cte->ctequery, buf, context->namespaces, NULL,
					  context->prettyFlags, context->wrapColumn,
					  context->indentLevel);
		if (PRETTY_INDENT(context))
			appendContextKeyword(context, "", 0, 0, 0);
		appendStringInfoChar(buf, ')');
		sep = ", ";
	}

	if (PRETTY_INDENT(context))
	{
		context->indentLevel -= PRETTYINDENT_STD;
		appendContextKeyword(context, "", 0, 0, 0);
	}
	else
		appendStringInfoChar(buf, ' ');
}
