resolve_polymorphic_argtypes(int numargs, Oid *argtypes, char *argmodes,
							 Node *call_expr)
{
	bool		have_anyelement_result = false;
	bool		have_anyarray_result = false;
	Oid			anyelement_type = InvalidOid;
	Oid			anyarray_type = InvalidOid;
	int			inargno;
	int			i;


	inargno = 0;
	for (i = 0; i < numargs; i++)
	{
		char		argmode = argmodes ? argmodes[i] : PROARGMODE_IN;

		switch (argtypes[i])
		{
			case ANYELEMENTOID:
			case ANYNONARRAYOID:
			case ANYENUMOID:
				if (argmode == PROARGMODE_OUT || argmode == PROARGMODE_TABLE)
					have_anyelement_result = true;
				else
				{
					if (!OidIsValid(anyelement_type))
					{
						anyelement_type = get_call_expr_argtype(call_expr,
																inargno);
						if (!OidIsValid(anyelement_type))
							return false;
					}
					argtypes[i] = anyelement_type;
				}
				break;
			case ANYARRAYOID:
				if (argmode == PROARGMODE_OUT || argmode == PROARGMODE_TABLE)
					have_anyarray_result = true;
				else
				{
					if (!OidIsValid(anyarray_type))
					{
						anyarray_type = get_call_expr_argtype(call_expr,
															  inargno);
						if (!OidIsValid(anyarray_type))
							return false;
					}
					argtypes[i] = anyarray_type;
				}
				break;
			default:
				break;
		}
		if (argmode != PROARGMODE_OUT && argmode != PROARGMODE_TABLE)
			inargno++;
	}


	if (!have_anyelement_result && !have_anyarray_result)
		return true;


	if (!OidIsValid(anyelement_type) && !OidIsValid(anyarray_type))
		return false;


	if (have_anyelement_result && !OidIsValid(anyelement_type))
		anyelement_type = resolve_generic_type(ANYELEMENTOID,
											   anyarray_type,
											   ANYARRAYOID);
	if (have_anyarray_result && !OidIsValid(anyarray_type))
		anyarray_type = resolve_generic_type(ANYARRAYOID,
											 anyelement_type,
											 ANYELEMENTOID);


	for (i = 0; i < numargs; i++)
	{
		switch (argtypes[i])
		{
			case ANYELEMENTOID:
			case ANYNONARRAYOID:
			case ANYENUMOID:
				argtypes[i] = anyelement_type;
				break;
			case ANYARRAYOID:
				argtypes[i] = anyarray_type;
				break;
			default:
				break;
		}
	}

	return true;
}
