double_chan_cb (session *lsess, GList **list)
{
	if (lsess->type == SESS_CHANNEL)
		*list = g_list_prepend(*list, lsess->channel);
	return TRUE;
}
