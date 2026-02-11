summary_get_selected_msg(SummaryView *summaryview)
{


	GList *sellist = GTK_CMCLIST(summaryview->ctree)->selection;

	if (sellist == NULL || sellist->next)
		return NULL;

	return GTKUT_CTREE_NODE_GET_ROW_DATA(sellist->data);
}
