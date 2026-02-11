gtt_xml_project_to_dom_tree (GttProject *prj)
{
	GList *children, *tasks;
	xmlNodePtr node, topnode;

	if (!prj) return NULL;
	topnode = xmlNewNode (NULL, BAD_CAST "gtt:project");

	node = xmlNewNode (NULL, BAD_CAST "title");
	xmlNodeAddContent(node, BAD_CAST gtt_project_get_title(prj));
	xmlAddChild (topnode, node);

	PUT_GUID ("guid", gtt_project_get_guid(prj));
	PUT_STR ("desc", gtt_project_get_desc(prj));
	PUT_STR ("notes", gtt_project_get_notes(prj));
	PUT_STR ("custid", gtt_project_get_custid(prj));

	PUT_INT ("id", gtt_project_get_id(prj));

	PUT_DBL ("billrate", gtt_project_get_billrate(prj));
	PUT_DBL ("overtime_rate", gtt_project_get_overtime_rate(prj));
	PUT_DBL ("overover_rate", gtt_project_get_overover_rate(prj));
	PUT_DBL ("flat_fee", gtt_project_get_flat_fee(prj));

	PUT_INT ("min_interval", gtt_project_get_min_interval(prj));
	PUT_INT ("auto_merge_interval", gtt_project_get_auto_merge_interval(prj));
	PUT_INT ("auto_merge_gap", gtt_project_get_auto_merge_gap(prj));

	PUT_LONG ("estimated_start", gtt_project_get_estimated_start(prj));
	PUT_LONG ("estimated_end", gtt_project_get_estimated_end(prj));
	PUT_LONG ("due_date", gtt_project_get_due_date(prj));

	PUT_INT ("sizing", gtt_project_get_sizing(prj));
	PUT_INT ("percent_complete", gtt_project_get_percent_complete(prj));

	PUT_ENUM_4 ("urgency", gtt_project_get_urgency(prj),
		UNDEFINED, LOW, MEDIUM, HIGH);
	PUT_ENUM_4 ("importance", gtt_project_get_importance(prj),
		UNDEFINED, LOW, MEDIUM, HIGH);
	PUT_ENUM_6 ("status", gtt_project_get_status(prj),
		NO_STATUS, NOT_STARTED, IN_PROGRESS, ON_HOLD, CANCELLED, COMPLETED);


	tasks = gtt_project_get_tasks(prj);
	node = gtt_task_list_to_dom_tree (tasks);
	xmlAddChild (topnode, node);


	children = gtt_project_get_children (prj);
	if (children)
	{
		node = gtt_project_list_to_dom_tree (children);
		xmlAddChild (topnode, node);
	}

	return topnode;
}
