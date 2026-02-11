sublist(Var list, int lower, int upper)
{
    if (lower > upper) {
	free_var(list);
	return new_list(0);
    } else {
	Var r;
	int i;

	r = new_list(upper - lower + 1);
	for (i = lower; i <= upper; i++)
	    r.v.list[i - lower + 1] = var_ref(list.v.list[i]);
	free_var(list);
	return r;
    }
}
