summary_select_prev_new(SummaryView *summaryview)
{
	GtkCMCTreeNode *node;
	gboolean skip_cur = FALSE;

	if (summaryview->displayed
	&&  summaryview->selected == summaryview->displayed) {
		debug_print("skipping current\n");
		skip_cur = TRUE;
	}

	node = summary_find_prev_flagged_msg
		(summaryview, summaryview->selected, MSG_NEW, skip_cur);

	if (!node || node == summaryview->selected) {
		AlertValue val = 0;

 		switch (prefs_common.next_unread_msg_dialog) {
 			case NEXTUNREADMSGDIALOG_ALWAYS:
				val = alertpanel(_("No more new messages"),
						 _("No new message found. "
						   "Search from the end?"),
						 GTK_STOCK_NO, "+"GTK_STOCK_YES, NULL);
 				break;
 			case NEXTUNREADMSGDIALOG_ASSUME_YES:
 				val = G_ALERTALTERNATE;
 				break;
 			case NEXTUNREADMSGDIALOG_ASSUME_NO:
 				val = !G_ALERTALTERNATE;
 				break;
 			default:
 				debug_print(
 					_("Internal error: unexpected value for prefs_common.next_unread_msg_dialog\n"));
 		}
		if (val != G_ALERTALTERNATE) return;
		node = summary_find_prev_flagged_msg(summaryview, NULL,
						     MSG_NEW, FALSE);
	}

	if (!node)
		alertpanel_notice(_("No new messages."));
	else
		summary_select_node(summaryview, node, TRUE, FALSE);
}
