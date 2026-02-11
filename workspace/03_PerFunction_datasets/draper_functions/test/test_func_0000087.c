build_pass (GSList *objects, GSList *ordered_list)
{
	GSList *retlist = NULL, *list;

	for (list = objects; list; list = list->next) {
		gboolean has_dep = FALSE;
		GSList *dep_list;
		if (g_slist_find (ordered_list, list->data))
			continue;
		for (dep_list = DB_OBJECT (list->data)->depend_list; dep_list; dep_list = dep_list->next) {
			if (!g_slist_find (ordered_list, dep_list->data)) {
				has_dep = TRUE;
				break;
			}
		}
		if (has_dep)
			continue;
		retlist = g_slist_prepend (retlist, list->data);
	}

#ifdef GDA_DEBUG_NO
	g_print (">> PASS\n");
	for (list = retlist; list; list = list->next)
		g_print ("--> %s\n", DB_OBJECT (list->data)->obj_name);
	g_print ("<<\n");
#endif

	return retlist;
}
