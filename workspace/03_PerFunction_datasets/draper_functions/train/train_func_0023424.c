make_viewdef(StringInfo buf, HeapTuple ruletup, TupleDesc rulettc,
			 int prettyFlags)
{
	Query	   *query;
	char		ev_type;
	Oid			ev_class;
	int2		ev_attr;
	bool		is_instead;
	char	   *ev_qual;
	char	   *ev_action;
	List	   *actions = NIL;
	Relation	ev_relation;
	int			fno;
	bool		isnull;


	fno = SPI_fnumber(rulettc, "ev_type");
	ev_type = (char) SPI_getbinval(ruletup, rulettc, fno, &isnull);

	fno = SPI_fnumber(rulettc, "ev_class");
	ev_class = (Oid) SPI_getbinval(ruletup, rulettc, fno, &isnull);

	fno = SPI_fnumber(rulettc, "ev_attr");
	ev_attr = (int2) SPI_getbinval(ruletup, rulettc, fno, &isnull);

	fno = SPI_fnumber(rulettc, "is_instead");
	is_instead = (bool) SPI_getbinval(ruletup, rulettc, fno, &isnull);

	fno = SPI_fnumber(rulettc, "ev_qual");
	ev_qual = SPI_getvalue(ruletup, rulettc, fno);

	fno = SPI_fnumber(rulettc, "ev_action");
	ev_action = SPI_getvalue(ruletup, rulettc, fno);
	if (ev_action != NULL)
		actions = (List *) stringToNode(ev_action);

	if (list_length(actions) != 1)
	{
		appendStringInfo(buf, "Not a view");
		return;
	}

	query = (Query *) linitial(actions);

	if (ev_type != '1' || ev_attr >= 0 || !is_instead ||
		strcmp(ev_qual, "<>") != 0 || query->commandType != CMD_SELECT)
	{
		appendStringInfo(buf, "Not a view");
		return;
	}

	ev_relation = heap_open(ev_class, AccessShareLock);

	get_query_def(query, buf, NIL, RelationGetDescr(ev_relation),
				  prettyFlags, 0);
	appendStringInfo(buf, ";");

	heap_close(ev_relation, AccessShareLock);
}
