gda_batch_serialize (GdaBatch *batch)
{
	GSList *list;
	GString *string;
	gchar *str;

	g_return_val_if_fail (GDA_IS_BATCH (batch), NULL);
	g_return_val_if_fail (batch->priv, NULL);

	string = g_string_new ("{");
	g_string_append (string, "\"statements\":");
	if (batch->priv->statements) {
		g_string_append_c (string, '[');
		for (list = batch->priv->statements; list; list = list->next) {
			str = gda_statement_serialize (GDA_STATEMENT (list->data));
			if (list != batch->priv->statements)
				g_string_append_c (string, ',');
			g_string_append (string, str);
			g_free (str);
		}
		g_string_append_c (string, ']');
	}
	else
		g_string_append (string, "null");
	g_string_append_c (string, '}');

	str = string->str;
	g_string_free (string, FALSE);
	return str;
}
