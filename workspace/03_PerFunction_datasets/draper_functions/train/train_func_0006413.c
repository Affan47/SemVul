table_cell_associate(table_row_t *r, const char *name, const char *value)
{
	table_cell_t *c;

	return_if_fail(r != NULL);
	return_if_fail(name != NULL);
	return_if_fail(value != NULL);

	c = scalloc(sizeof(table_cell_t), 1);

	c->name = sstrdup(name);
	c->value = sstrdup(value);

	mowgli_node_add(c, mowgli_node_create(), &r->cells);
}
