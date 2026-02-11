table_row_new(table_t *t)
{
	table_row_t *out;

	return_val_if_fail(t != NULL, NULL);

	out = scalloc(sizeof(table_row_t), 1);

	mowgli_node_add(out, mowgli_node_create(), &t->rows);

	return out;
}
