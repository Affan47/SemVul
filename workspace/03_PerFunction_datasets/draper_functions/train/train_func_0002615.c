summary_redisplay_msg(SummaryView *summaryview)
{
	GtkCMCTreeNode *node;

	if (summaryview->displayed) {
		node = summaryview->displayed;
		summaryview->displayed = NULL;
		summary_display_msg(summaryview, node);
	}
}
