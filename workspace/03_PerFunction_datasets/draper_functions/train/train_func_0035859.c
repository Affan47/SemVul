table_specification_end_element (GMarkupParseContext *context,
                                 const gchar *element_name,
                                 gpointer user_data,
                                 GError **error)
{
	ETableSpecification *specification;

	specification = E_TABLE_SPECIFICATION (user_data);

	if (g_str_equal (element_name, "ETableState")) {
		ETableState *state;

		state = e_table_state_parse_context_pop (context);
		g_return_if_fail (E_IS_TABLE_STATE (state));

		g_clear_object (&specification->state);
		specification->state = g_object_ref (state);

		g_object_unref (state);
	}
}
