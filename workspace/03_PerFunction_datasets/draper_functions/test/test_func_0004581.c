ResolveNew_callback(Var *var,
					replace_rte_variables_context *context)
{
	ResolveNew_context *rcon = (ResolveNew_context *) context->callback_arg;
	TargetEntry *tle;

	if (var->varattno == InvalidAttrNumber)
	{

		RowExpr    *rowexpr;
		List	   *colnames;
		List	   *fields;


		expandRTE(rcon->target_rte,
				  var->varno, var->varlevelsup, var->location,
				  (var->vartype != RECORDOID),
				  &colnames, &fields);

		fields = (List *) replace_rte_variables_mutator((Node *) fields,
														context);
		rowexpr = makeNode(RowExpr);
		rowexpr->args = fields;
		rowexpr->row_typeid = var->vartype;
		rowexpr->row_format = COERCE_IMPLICIT_CAST;
		rowexpr->colnames = colnames;
		rowexpr->location = var->location;

		return (Node *) rowexpr;
	}


	tle = get_tle_by_resno(rcon->targetlist, var->varattno);

	if (tle == NULL || tle->resjunk)
	{

		if (rcon->event == CMD_UPDATE)
		{

			var = (Var *) copyObject(var);
			var->varno = rcon->update_varno;
			var->varnoold = rcon->update_varno;
			return (Node *) var;
		}
		else
		{


			return coerce_to_domain((Node *) makeNullConst(var->vartype,
														   var->vartypmod),
									InvalidOid, -1,
									var->vartype,
									COERCE_IMPLICIT_CAST,
									-1,
									false,
									false);
		}
	}
	else
	{

		Node	   *newnode = copyObject(tle->expr);


		if (var->varlevelsup > 0)
			IncrementVarSublevelsUp(newnode, var->varlevelsup, 0);

		return newnode;
	}
}
