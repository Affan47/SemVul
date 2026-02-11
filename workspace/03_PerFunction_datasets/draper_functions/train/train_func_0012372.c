dcc_show_list (struct session *sess)
{
	int i = 0;
	struct DCC *dcc;
	GSList *list = dcc_list;

	EMIT_SIGNAL (XP_TE_DCCHEAD, sess, NULL, NULL, NULL, NULL, 0);
	while (list)
	{
		dcc = (struct DCC *) list->data;
		i++;
		PrintTextf (sess, " %s  %-10.10s %-7.7s %-7"DCC_SFMT" %-7"DCC_SFMT" %s\n",
					 dcctypes[dcc->type], dcc->nick,
					 _(dccstat[dcc->dccstat].name), dcc->size, dcc->pos,
					 file_part (dcc->file));
		list = list->next;
	}
	if (!i)
		PrintText (sess, _("No active DCCs\n"));
}
