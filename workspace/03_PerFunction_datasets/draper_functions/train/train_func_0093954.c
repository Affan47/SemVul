fe_add_chan_list (server *serv, char *chan, char *users, char *topic)
{
	chanlistrow *next_row;
	int len = strlen (chan) + 1;


	next_row = malloc (sizeof (chanlistrow) + len);
	memcpy (((char *)next_row) + sizeof (chanlistrow), chan, len);
	next_row->topic = strip_color (topic, -1, STRIP_ALL);
	next_row->collation_key = g_utf8_collate_key (chan, len-1);
	if (!(next_row->collation_key))
		next_row->collation_key = g_strdup (chan);
	next_row->users = atoi (users);


	serv->gui->chanlist_data_stored_rows =
		g_slist_prepend (serv->gui->chanlist_data_stored_rows, next_row);


	chanlist_place_row_in_gui (serv, next_row, FALSE);
}
