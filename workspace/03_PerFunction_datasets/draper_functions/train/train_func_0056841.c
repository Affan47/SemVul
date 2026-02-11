lookup_agg_function(List *fnName,
					int nargs,
					Oid *input_types,
					Oid *rettype)
{
	Oid			fnOid;
	bool		retset;
	Oid		   *true_oid_array;
	FuncDetailCode fdresult;
	AclResult	aclresult;
	int			i;


	fdresult = func_get_detail(fnName, NIL, nargs, input_types,
							   &fnOid, rettype, &retset,
							   &true_oid_array);


	if (fdresult != FUNCDETAIL_NORMAL || !OidIsValid(fnOid))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_FUNCTION),
				 errmsg("function %s does not exist",
						func_signature_string(fnName, nargs, input_types))));
	if (retset)
		ereport(ERROR,
				(errcode(ERRCODE_DATATYPE_MISMATCH),
				 errmsg("function %s returns a set",
						func_signature_string(fnName, nargs, input_types))));


	*rettype = enforce_generic_type_consistency(input_types,
												true_oid_array,
												nargs,
												*rettype,
												true);


	for (i = 0; i < nargs; i++)
	{
		if (!IsPolymorphicType(true_oid_array[i]) &&
			!IsBinaryCoercible(input_types[i], true_oid_array[i]))
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("function %s requires run-time type coercion",
					 func_signature_string(fnName, nargs, true_oid_array))));
	}


	aclresult = pg_proc_aclcheck(fnOid, GetUserId(), ACL_EXECUTE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, ACL_KIND_PROC, get_func_name(fnOid));

	return fnOid;
}
