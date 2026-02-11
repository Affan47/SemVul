procmsg_get_number_list_for_msgs(MsgInfoList *msglist)
{
	GSList *cur = NULL;
	GSList *nums = NULL;

	for (cur = msglist; cur; cur = cur->next) {
		MsgInfo *msg = (MsgInfo *)cur->data;
		nums = g_slist_prepend(nums, GUINT_TO_POINTER(msg->msgnum));
	}

	return g_slist_reverse(nums);
}
