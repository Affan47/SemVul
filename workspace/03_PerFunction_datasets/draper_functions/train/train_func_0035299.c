msginfo_mark_as_read (SummaryView *summaryview, MsgInfo *msginfo,
				      GtkCMCTreeNode *row)
{
	cm_return_if_fail(summaryview != NULL);
	cm_return_if_fail(msginfo != NULL);
	cm_return_if_fail(row != NULL);

	if (MSG_IS_NEW(msginfo->flags) || MSG_IS_UNREAD(msginfo->flags)) {
		summary_msginfo_unset_flags
			(msginfo, MSG_NEW | MSG_UNREAD, 0);
		summary_set_row_marks(summaryview, row);
		summary_status_show(summaryview);
	}
}
