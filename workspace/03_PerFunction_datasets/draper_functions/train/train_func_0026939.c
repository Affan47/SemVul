Callback_GetGame_Unselect(GtkWidget* clist, gint row)  {
	(void)clist;
	(void)row;

	if(global->selected_host)  g_free(global->selected_host);
	if(global->selected_gametype)  g_free(global->selected_gametype);
	global->selected_host = 0;
	global->selected_port = 0;
	global->selected_gametype = 0;
	global->selected_gameid = 0;
}
