get_op_btree_interpretation(Oid opno, List **opclasses, List **opstrats)
{
	Oid			lefttype,
				righttype;
	CatCList   *catlist;
	bool		op_negated;
	int			i;

	*opclasses = NIL;
	*opstrats = NIL;


	op_input_types(opno, &lefttype, &righttype);
	Assert(OidIsValid(lefttype));


	catlist = SearchSysCacheList(AMOPOPID, 1,
								 ObjectIdGetDatum(opno),
								 0, 0, 0);


	op_negated = false;
	if (catlist->n_members == 0)
	{
		Oid			op_negator = get_negator(opno);

		if (OidIsValid(op_negator))
		{
			op_negated = true;
			ReleaseSysCacheList(catlist);
			catlist = SearchSysCacheList(AMOPOPID, 1,
										 ObjectIdGetDatum(op_negator),
										 0, 0, 0);
		}
	}


	for (i = 0; i < catlist->n_members; i++)
	{
		HeapTuple	op_tuple = &catlist->members[i]->tuple;
		Form_pg_amop op_form = (Form_pg_amop) GETSTRUCT(op_tuple);
		Oid			opclass_id;
		StrategyNumber op_strategy;

		opclass_id = op_form->amopclaid;


		if (!opclass_is_btree(opclass_id))
			continue;


		if (get_opclass_input_type(opclass_id) != lefttype)
			continue;


		op_strategy = (StrategyNumber) op_form->amopstrategy;
		Assert(op_strategy >= 1 && op_strategy <= 5);

		if (op_negated)
		{

			if (op_strategy != BTEqualStrategyNumber)
				continue;
			op_strategy = ROWCOMPARE_NE;
		}

		*opclasses = lappend_oid(*opclasses, opclass_id);
		*opstrats = lappend_int(*opstrats, op_strategy);
	}

	ReleaseSysCacheList(catlist);
}
