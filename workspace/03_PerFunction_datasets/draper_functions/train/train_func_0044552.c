get_nth_arg(Module_table *mpt, int n)
{
    Operand *arg;
    int i;

    for (i = 1, arg = mpt->arg_head;
	 i < n;
	 i++, arg = arg->next);

    return arg;
}
