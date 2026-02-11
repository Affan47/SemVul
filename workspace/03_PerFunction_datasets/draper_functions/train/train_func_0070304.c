mergejoinscansel(PlannerInfo *root, Node *clause,
				 Selectivity *leftscan,
				 Selectivity *rightscan)
{
	Node	   *left,
			   *right;
	VariableStatData leftvar,
				rightvar;
	Oid			lefttype,
				righttype;
	Oid			opno,
				lsortop,
				rsortop,
				ltop,
				gtop,
				leop,
				revgtop,
				revleop;
	Datum		leftmax,
				rightmax;
	double		selec;


	*leftscan = *rightscan = 1.0;


	if (!is_opclause(clause))
		return;
	opno = ((OpExpr *) clause)->opno;
	left = get_leftop((Expr *) clause);
	right = get_rightop((Expr *) clause);
	if (!right)
		return;


	examine_variable(root, left, 0, &leftvar);
	examine_variable(root, right, 0, &rightvar);


	lefttype = exprType(left);
	righttype = exprType(right);


	if (!op_mergejoinable(opno,
						  &lsortop,
						  &rsortop))
		goto fail;


	if (!get_variable_maximum(root, &leftvar, lsortop, &leftmax))
		goto fail;

	if (!get_variable_maximum(root, &rightvar, rsortop, &rightmax))
		goto fail;


	op_mergejoin_crossops(opno, &ltop, &gtop, NULL, NULL);


	leop = get_negator(gtop);
	if (!OidIsValid(leop))
		goto fail;


	revgtop = get_commutator(ltop);
	if (!OidIsValid(revgtop))
		goto fail;


	revleop = get_negator(revgtop);
	if (!OidIsValid(revleop))
		goto fail;


	selec = scalarineqsel(root, leop, false, &leftvar,
						  rightmax, righttype);
	if (selec != DEFAULT_INEQ_SEL)
		*leftscan = selec;


	selec = scalarineqsel(root, revleop, false, &rightvar,
						  leftmax, lefttype);
	if (selec != DEFAULT_INEQ_SEL)
		*rightscan = selec;


	if (*leftscan > *rightscan)
		*leftscan = 1.0;
	else if (*leftscan < *rightscan)
		*rightscan = 1.0;
	else
		*leftscan = *rightscan = 1.0;

fail:
	ReleaseVariableStats(leftvar);
	ReleaseVariableStats(rightvar);
}
