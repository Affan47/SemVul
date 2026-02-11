add_response_cb (GtkDialog *dialog, int response, gpointer user_data)
{
	VgRuleList *list = user_data;
	GtkWidget *editor;
	GtkTreeIter iter;
	RuleNode *node;
	VgRule *rule;

	if (response == GTK_RESPONSE_OK) {
		const char *name;
		GtkWidget *msg;

		editor = g_object_get_data ((GObject *) dialog, "editor");

		name = vg_rule_editor_get_name ((VgRuleEditor *) editor);
		if (!name || *name == '\0') {
			msg = gtk_message_dialog_new ((GtkWindow *) dialog, GTK_DIALOG_MODAL |
						      GTK_DIALOG_DESTROY_WITH_PARENT,
						      GTK_MESSAGE_WARNING,
						      GTK_BUTTONS_CLOSE,
						      _("You have forgotten to name your suppression rule."));

			gtk_dialog_run ((GtkDialog *) msg);
			gtk_widget_destroy (msg);
			return;
		}

		list->changed = TRUE;

		rule = vg_rule_editor_get_rule ((VgRuleEditor *) editor);

		node = g_new (RuleNode, 1);
		node->rule = rule;

		list_append_node (&list->rules, (ListNode *) node);

		vg_rule_list_save (list);

		gtk_list_store_append ((GtkListStore *) list->model, &iter);

		gtk_list_store_set ((GtkListStore *) list->model, &iter,
				    COL_STRING_NAME, rule->name,
				    COL_POINTER_RULE, rule,
				    COL_POINTER_RULE_NODE, node, -1);

		g_signal_emit (list, signals[RULE_ADDED], 0, rule);
	}

	gtk_widget_destroy ((GtkWidget *) dialog);
}
