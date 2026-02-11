setadd(Var list, Var value)
{
    if (ismember(value, list, 0)) {
	free_var(value);
	return list;
    }
    return listappend(list, value);
}
