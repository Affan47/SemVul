transformConstraintAttrs(List *constraintList)
{
	Node	   *lastprimarynode = NULL;
	bool		saw_deferrability = false;
	bool		saw_initially = false;
	ListCell   *clist;

	foreach(clist, constraintList)
	{
		Node	   *node = lfirst(clist);

		if (!IsA(node, Constraint))
		{
			lastprimarynode = node;

			saw_deferrability = false;
			saw_initially = false;
		}
		else
		{
			Constraint *con = (Constraint *) node;

			switch (con->contype)
			{
				case CONSTR_ATTR_DEFERRABLE:
					if (lastprimarynode == NULL ||
						!IsA(lastprimarynode, FkConstraint))
						ereport(ERROR,
								(errcode(ERRCODE_SYNTAX_ERROR),
								 errmsg("misplaced DEFERRABLE clause")));
					if (saw_deferrability)
						ereport(ERROR,
								(errcode(ERRCODE_SYNTAX_ERROR),
								 errmsg("multiple DEFERRABLE/NOT DEFERRABLE clauses not allowed")));
					saw_deferrability = true;
					((FkConstraint *) lastprimarynode)->deferrable = true;
					break;
				case CONSTR_ATTR_NOT_DEFERRABLE:
					if (lastprimarynode == NULL ||
						!IsA(lastprimarynode, FkConstraint))
						ereport(ERROR,
								(errcode(ERRCODE_SYNTAX_ERROR),
								 errmsg("misplaced NOT DEFERRABLE clause")));
					if (saw_deferrability)
						ereport(ERROR,
								(errcode(ERRCODE_SYNTAX_ERROR),
								 errmsg("multiple DEFERRABLE/NOT DEFERRABLE clauses not allowed")));
					saw_deferrability = true;
					((FkConstraint *) lastprimarynode)->deferrable = false;
					if (saw_initially &&
						((FkConstraint *) lastprimarynode)->initdeferred)
						ereport(ERROR,
								(errcode(ERRCODE_SYNTAX_ERROR),
								 errmsg("constraint declared INITIALLY DEFERRED must be DEFERRABLE")));
					break;
				case CONSTR_ATTR_DEFERRED:
					if (lastprimarynode == NULL ||
						!IsA(lastprimarynode, FkConstraint))
						ereport(ERROR,
								(errcode(ERRCODE_SYNTAX_ERROR),
							 errmsg("misplaced INITIALLY DEFERRED clause")));
					if (saw_initially)
						ereport(ERROR,
								(errcode(ERRCODE_SYNTAX_ERROR),
								 errmsg("multiple INITIALLY IMMEDIATE/DEFERRED clauses not allowed")));
					saw_initially = true;
					((FkConstraint *) lastprimarynode)->initdeferred = true;


					if (!saw_deferrability)
						((FkConstraint *) lastprimarynode)->deferrable = true;
					else if (!((FkConstraint *) lastprimarynode)->deferrable)
						ereport(ERROR,
								(errcode(ERRCODE_SYNTAX_ERROR),
								 errmsg("constraint declared INITIALLY DEFERRED must be DEFERRABLE")));
					break;
				case CONSTR_ATTR_IMMEDIATE:
					if (lastprimarynode == NULL ||
						!IsA(lastprimarynode, FkConstraint))
						ereport(ERROR,
								(errcode(ERRCODE_SYNTAX_ERROR),
							errmsg("misplaced INITIALLY IMMEDIATE clause")));
					if (saw_initially)
						ereport(ERROR,
								(errcode(ERRCODE_SYNTAX_ERROR),
								 errmsg("multiple INITIALLY IMMEDIATE/DEFERRED clauses not allowed")));
					saw_initially = true;
					((FkConstraint *) lastprimarynode)->initdeferred = false;
					break;
				default:

					lastprimarynode = node;

					saw_deferrability = false;
					saw_initially = false;
					break;
			}
		}
	}
}
