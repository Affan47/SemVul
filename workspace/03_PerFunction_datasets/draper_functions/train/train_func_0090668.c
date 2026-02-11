extract_arg_types (GnmFunc *def)
{
	int i;

	function_def_count_args (def,
				 &def->fn.args.min_args,
				 &def->fn.args.max_args);
	def->fn.args.arg_types = g_malloc (def->fn.args.max_args + 1);
	for (i = 0; i < def->fn.args.max_args; i++)
		def->fn.args.arg_types[i] = function_def_get_arg_type (def, i);
	def->fn.args.arg_types[i] = 0;
}
