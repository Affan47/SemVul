_set_active_combo_part(GtkComboBox *combo,
				   GtkTreeModel *model, GtkTreeIter *iter,
				   int type)
{
	char *temp_char = NULL;
	int action = 0;
	int i = 0, unknown_found = 0;
	char *upper = NULL;

	if (model)
		gtk_tree_model_get(model, iter, type, &temp_char, -1);
	if (!temp_char)
		goto end_it;
	switch(type) {
	case SORTID_DEFAULT:
	case SORTID_HIDDEN:
	case SORTID_ROOT:
		if (!strcmp(temp_char, "yes"))
			action = 0;
		else if (!strcmp(temp_char, "no"))
			action = 1;
		else
			action = 0;

		break;
	case SORTID_SHARE:
		if (!strncmp(temp_char, "force", 5))
			action = 0;
		else if (!strcmp(temp_char, "no"))
			action = 1;
		else if (!strncmp(temp_char, "yes", 3))
			action = 2;
		else if (!strcmp(temp_char, "exclusive"))
			action = 3;
		else
			action = 0;
		break;
	case SORTID_PART_STATE:
		if (!strcmp(temp_char, "up"))
			action = 0;
		else if (!strcmp(temp_char, "down"))
			action = 1;
		else if (!strcmp(temp_char, "inactive"))
			action = 2;
		else if (!strcmp(temp_char, "drain"))
			action = 3;
		else
			action = 0;
		break;
	case SORTID_NODE_STATE:
		if (!strcasecmp(temp_char, "drain"))
			action = 0;
		else if (!strcasecmp(temp_char, "resume"))
			action = 1;
		else
			for(i = 0; i < NODE_STATE_END; i++) {
				upper = node_state_string(i);
				if (!strcmp(upper, "UNKNOWN")) {
					unknown_found++;
					continue;
				}

				if (!strcasecmp(temp_char, upper)) {
					action = i + 2 - unknown_found;
					break;
				}
			}

		break;
	case SORTID_PREEMPT_MODE:
		if (!strcasecmp(temp_char, "cancel"))
			action = 0;
		else if (!strcasecmp(temp_char, "checkpoint"))
			action = 1;
		else if (!strcasecmp(temp_char, "off"))
			action = 2;
		else if (!strcasecmp(temp_char, "requeue"))
			action = 3;
		else if (!strcasecmp(temp_char, "suspend"))
			action = 4;
		else
			action = 2;
		break;
	default:
		break;
	}
	g_free(temp_char);
end_it:
	gtk_combo_box_set_active(combo, action);

}
