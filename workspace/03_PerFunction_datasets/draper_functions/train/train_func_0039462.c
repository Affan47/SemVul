ms_container_parse_expr (MSContainer *c, guint8 const *data, int length)
{
	g_return_val_if_fail (c != NULL, NULL);
	g_return_val_if_fail (c->vtbl != NULL, NULL);
	g_return_val_if_fail (c->vtbl->parse_expr != NULL, NULL);
	if (length == 0)
		return NULL;
	return (*c->vtbl->parse_expr) (c, data, length);
}
