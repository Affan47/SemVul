gda_sql_select_from_copy (GdaSqlSelectFrom *from)
{
	GdaSqlSelectFrom *copy;
	GSList *list;

	if (!from) return NULL;

	copy = gda_sql_select_from_new (NULL);
	for (list = from->targets; list; list = list->next) {
		copy->targets = g_slist_prepend (copy->targets,
						 gda_sql_select_target_copy ((GdaSqlSelectTarget *) list->data));
		gda_sql_any_part_set_parent (copy->targets->data, copy);
	}
	copy->targets = g_slist_reverse (copy->targets);

	for (list = from->joins; list; list = list->next) {
		copy->joins = g_slist_prepend (copy->joins,
					       gda_sql_select_join_copy ((GdaSqlSelectJoin *) list->data));
		gda_sql_any_part_set_parent (copy->joins->data, copy);
	}
	copy->joins = g_slist_reverse (copy->joins);

	return copy;
}
