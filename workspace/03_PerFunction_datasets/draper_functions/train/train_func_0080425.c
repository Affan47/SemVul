parse_project (xmlNodePtr project)
{
	xmlNodePtr node;
	GttProject *prj = NULL;

	if (!project) { gtt_err_set_code (GTT_FILE_CORRUPT); return prj; }

	if (strcmp ("project", (char *)project->name)) {
		gtt_err_set_code (GTT_FILE_CORRUPT); return prj; }

	prj = gtt_project_new ();
	gtt_project_freeze (prj);
	for (node=project->xmlChildrenNode; node; node=node->next)
	{
		if (node->type != XML_ELEMENT_NODE) continue;

		GET_GUID (prj, gtt_project_set_guid, "guid")
		GET_STR (prj, gtt_project_set_title, "title")
		GET_STR (prj, gtt_project_set_desc, "desc")
		GET_STR (prj, gtt_project_set_notes, "notes")
		GET_STR (prj, gtt_project_set_custid, "custid")

		GET_DBL (prj, gtt_project_set_billrate, "billrate")
		GET_DBL (prj, gtt_project_set_overtime_rate, "overtime_rate")
		GET_DBL (prj, gtt_project_set_overover_rate, "overover_rate")
		GET_DBL (prj, gtt_project_set_flat_fee, "flat_fee")

		GET_INT (prj, gtt_project_set_min_interval, "min_interval")
		GET_INT (prj, gtt_project_set_auto_merge_interval, "auto_merge_interval")
		GET_INT (prj, gtt_project_set_auto_merge_gap, "auto_merge_gap")

		GET_INT (prj, gtt_project_set_id, "id")

		GET_TIM (prj, gtt_project_set_estimated_start, "estimated_start")
		GET_TIM (prj, gtt_project_set_estimated_end, "estimated_end")
		GET_TIM (prj, gtt_project_set_due_date, "due_date")
		GET_INT (prj, gtt_project_set_sizing, "sizing")
		GET_INT (prj, gtt_project_set_percent_complete, "percent_complete")

		GET_ENUM_4 (prj, gtt_project_set_urgency, "urgency",
			UNDEFINED, LOW, MEDIUM, HIGH)
		GET_ENUM_4 (prj, gtt_project_set_importance, "importance",
			UNDEFINED, LOW, MEDIUM, HIGH)
		GET_ENUM_6 (prj, gtt_project_set_status, "status",
			NO_STATUS, NOT_STARTED, IN_PROGRESS, ON_HOLD, CANCELLED, COMPLETED)

			if (0 == strcmp ("task-list", (char *)node->name))
		{
			xmlNodePtr tn;
			for (tn=node->xmlChildrenNode; tn; tn=tn->next)
			{
				GttTask *tsk;
				tsk = parse_task (tn);
				gtt_project_append_task (prj, tsk);
			}
		}
		else
			if (0 == strcmp ("project-list", (char *)node->name))
		{
			xmlNodePtr tn;
			for (tn=node->xmlChildrenNode; tn; tn=tn->next)
			{
				GttProject *child;
				if (tn->type != XML_ELEMENT_NODE) continue;
				child = parse_project (tn);
				gtt_project_append_project (prj, child);
			}
		}
		else
		{
			g_warning ("unexpected node %s", node->name);
			gtt_err_set_code (GTT_UNKNOWN_TOKEN);
		}
	}
	gtt_project_thaw (prj);
	return prj;
}
