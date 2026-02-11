check_func_arg_check_method(Method *m)
{
	GList *li;
	for(li = m->args; li; li = li->next) {
		FuncArg *fa = li->data;
		check_func_arg_check_func_arg(m, fa);
	}
}
