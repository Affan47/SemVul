tracker_data_insert_statement (const gchar            *graph,
                               const gchar            *subject,
                               const gchar            *predicate,
                               const gchar            *object,
                               GError                **error)
{
	TrackerProperty *property;

	g_return_if_fail (subject != NULL);
	g_return_if_fail (predicate != NULL);
	g_return_if_fail (object != NULL);
	g_return_if_fail (in_transaction);

	property = tracker_ontologies_get_property_by_uri (predicate);
	if (property != NULL) {
		if (tracker_property_get_data_type (property) == TRACKER_PROPERTY_TYPE_RESOURCE) {
			tracker_data_insert_statement_with_uri (graph, subject, predicate, object, error);
		} else {
			tracker_data_insert_statement_with_string (graph, subject, predicate, object, error);
		}
	} else {
		g_set_error (error, TRACKER_SPARQL_ERROR, TRACKER_SPARQL_ERROR_UNKNOWN_PROPERTY,
		             "Property '%s' not found in the ontology", predicate);
	}
}
