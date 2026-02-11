CallBack_menu_DeclareBankrupcy(GtkWidget* widget)  {
	(void)widget;

	gchar *sendstr;

	if(global->phase < PHASE_GAMEPLAY) return;

	sendstr = g_strdup_printf(".D\n");
	client_send(game->connectid, sendstr, strlen(sendstr));
	g_free(sendstr);
}
