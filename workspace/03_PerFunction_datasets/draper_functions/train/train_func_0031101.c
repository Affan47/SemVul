copy_flags (Flags * self)
{
	Flags * new;
	g_return_val_if_fail (self != NULL, NULL);
	g_return_val_if_fail (self->type == FLAGS_NODE, NULL);
	new = g_new0(Flags, 1);
	new->type = FLAGS_NODE;
	new->ftype = g_strdup (self->ftype);
	new->prefix = g_strdup (self->prefix);
	new->values = g_list_copy (self->values); COPY_LIST_VALS(new->values, g_strdup);
	return new;
}
