expandTupleDesc(TupleDesc tupdesc, Alias *eref,
				int rtindex, int sublevels_up,
				int location, bool include_dropped,
				List **colnames, List **colvars)
{
	int			maxattrs = tupdesc->natts;
	int			numaliases = list_length(eref->colnames);
	int			varattno;

	for (varattno = 0; varattno < maxattrs; varattno++)
	{
		Form_pg_attribute attr = tupdesc->attrs[varattno];

		if (attr->attisdropped)
		{
			if (include_dropped)
			{
				if (colnames)
					*colnames = lappend(*colnames, makeString(pstrdup("")));
				if (colvars)
				{


					*colvars = lappend(*colvars, makeNullConst(INT4OID, -1));
				}
			}
			continue;
		}

		if (colnames)
		{
			char	   *label;

			if (varattno < numaliases)
				label = strVal(list_nth(eref->colnames, varattno));
			else
				label = NameStr(attr->attname);
			*colnames = lappend(*colnames, makeString(pstrdup(label)));
		}

		if (colvars)
		{
			Var		   *varnode;

			varnode = makeVar(rtindex, attr->attnum,
							  attr->atttypid, attr->atttypmod,
							  sublevels_up);
			varnode->location = location;

			*colvars = lappend(*colvars, varnode);
		}
	}
}
