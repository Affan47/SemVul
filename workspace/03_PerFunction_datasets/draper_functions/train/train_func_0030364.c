fe_add_ban_list (struct session *sess, char *mask, char *who, char *when, int rplcode)
{
	banlist_info *banl = sess->res->banlist;
	int i;
	GtkListStore *store;
	GtkTreeIter iter;

	if (!banl)
		return FALSE;

	for (i = 0; i < MODE_CT; i++)
		if (modes[i].code == rplcode)
			break;
	if (i == MODE_CT)
	{

		return FALSE;
	}
	if (banl->pending & 1<<i)
	{
		store = get_store (sess);
		gtk_list_store_append (store, &iter);

		gtk_list_store_set (store, &iter, TYPE_COLUMN, _(modes[i].type), MASK_COLUMN, mask,
						FROM_COLUMN, who, DATE_COLUMN, when, -1);

		banl->line_ct++;
		return TRUE;
	}
	else return FALSE;
}
