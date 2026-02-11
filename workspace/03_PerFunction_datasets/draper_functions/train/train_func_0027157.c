copy_funcarg (FuncArg * self)
{
	FuncArg * new;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (self->type == FUNCARG_NODE, NULL);
	new = g_new0(FuncArg, 1);
	new->type = FUNCARG_NODE;
	new->atype = copy_type (self->atype);
	new->name = g_strdup (self->name);
	new->checks = node_list_copy (self->checks);
	return new;
}
