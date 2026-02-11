function_call_with_values (GnmEvalPos const *ep, char const *fn_name,
			   int argc, GnmValue const * const *values)
{
	GnmFunc *fn_def;

	g_return_val_if_fail (ep != NULL, NULL);
	g_return_val_if_fail (fn_name != NULL, NULL);
	g_return_val_if_fail (ep->sheet != NULL, NULL);


	fn_def = gnm_func_lookup (fn_name, NULL);
	if (fn_def == NULL)
		return value_new_error_NAME (ep);
	return function_def_call_with_values (ep, fn_def, argc, values);
}
