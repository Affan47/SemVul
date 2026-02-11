simplify_function(Oid funcid, Oid result_type, int32 result_typmod,
				  Oid result_collid, Oid input_collid, List **args,
				  bool has_named_args,
				  bool allow_inline,
				  eval_const_expressions_context *context)
{
	HeapTuple	func_tuple;
	Expr	   *newexpr;


	func_tuple = SearchSysCache1(PROCOID, ObjectIdGetDatum(funcid));
	if (!HeapTupleIsValid(func_tuple))
		elog(ERROR, "cache lookup failed for function %u", funcid);


	if (has_named_args)
		*args = reorder_function_arguments(*args, result_type, func_tuple,
										   context);
	else if (((Form_pg_proc) GETSTRUCT(func_tuple))->pronargs > list_length(*args))
		*args = add_function_defaults(*args, result_type, func_tuple, context);

	newexpr = evaluate_function(funcid, result_type, result_typmod,
								result_collid, input_collid, *args,
								func_tuple, context);

	if (!newexpr && allow_inline)
		newexpr = inline_function(funcid, result_type, result_collid,
								  input_collid, *args,
								  func_tuple, context);

	ReleaseSysCache(func_tuple);

	return newexpr;
}
