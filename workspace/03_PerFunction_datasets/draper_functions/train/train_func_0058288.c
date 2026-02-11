summary_display_msg_selected(SummaryView *summaryview,
				  gboolean all_headers)
{
	if (summary_is_locked(summaryview)) return;
	summaryview->displayed = NULL;
	summary_display_msg_full(summaryview, summaryview->selected, FALSE,
				 all_headers);
}
