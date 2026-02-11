summary_set_colorlabel(SummaryView *summaryview, guint labelcolor,
			    GtkWidget *widget)
{
	GtkCMCTree *ctree = GTK_CMCTREE(summaryview->ctree);
	GList *cur;
	gboolean froze = FALSE;

	START_LONG_OPERATION(summaryview, FALSE);
	for (cur = GTK_CMCLIST(ctree)->selection; cur != NULL && cur->data != NULL; cur = cur->next)
		summary_set_row_colorlabel(summaryview,
					   GTK_CMCTREE_NODE(cur->data), labelcolor);
	END_LONG_OPERATION(summaryview);
}
