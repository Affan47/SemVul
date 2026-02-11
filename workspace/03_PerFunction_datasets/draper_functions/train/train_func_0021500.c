real_run_at_node (GdaReportEngine *engine, xmlNodePtr topnode, RunContext *context, GError **error)
{
	xmlNodePtr node;
	xmlNodePtr next_node = NULL;
	for (node = topnode; node; node = next_node) {
		next_node = node->next;

		if (!strncmp ((gchar *) node->name, "gda_report", 10)) {
			GSList *created_nodes = NULL;
			gboolean cmd_res = TRUE;
			gsize i;
			gboolean command_found = FALSE;

			for (i = 0; i < sizeof (commands) / sizeof (EngineCommand); i++) {
				EngineCommand *ec = (EngineCommand *) &(commands [i]);
				if (ec->has_prefix) {
					if (!strcmp (((gchar *) node->name) + 10, ec->tag_name + 10)) {
						command_found = TRUE;
						if (ec->func)
							cmd_res = (ec->func) (engine, node, &created_nodes, context, error);
						break;
					}
				}
			}
			if (!command_found) {

				TO_IMPLEMENT;
				g_warning ("Engine command '%s' is not yet implemented", (gchar *) node->name);
			}

			if (created_nodes) {

				GSList *list;
				for (list = created_nodes; list; list = list->next) {
					next_node = xmlAddPrevSibling (node, (xmlNodePtr) list->data);
					g_assert (next_node);
				}
				g_slist_free (created_nodes);


				xmlUnlinkNode (node);
				xmlFreeNode (node);
				next_node = next_node->next;
			}
			else {

				xmlUnlinkNode (node);
				xmlFreeNode (node);
			}
			if (!cmd_res)
				return FALSE;
		}
		else if (node->children) {
			if (!real_run_at_node (engine, node->children, context, error))
				return FALSE;
		}
	}
	return TRUE;
}
