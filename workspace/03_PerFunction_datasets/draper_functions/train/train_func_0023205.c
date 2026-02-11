gmlc_gui_server_tab_help_display_help_topic(GmlcGuiServerTabHelp * pGmlcGuiSrvTabHelp) {
	GmlcMysqlQuery * pGmlcMysqlQry = NULL;
	GtkTextBuffer * txtBuffer = NULL;
	GArray * arRow = NULL;
	gchar * pcSql = NULL, * pcTopic = NULL;
	gchar * pcName = NULL, * pcDescription = NULL, * pcSample = NULL, * pcUrl = NULL;

	pGmlcMysqlQry = gmlc_mysql_query_new(pGmlcGuiSrvTabHelp->pGmlcMysqlSrv, "mysql");

	pcSql = g_strdup_printf("SELECT * FROM `mysql`.`help_topic` WHERE help_topic_id = %d", pGmlcGuiSrvTabHelp->iCurrentTopic);

	if (gmlc_mysql_query_execute(pGmlcMysqlQry, pcSql, strlen(pcSql), FALSE)) {
		arRow = gmlc_mysql_query_next_record(pGmlcMysqlQry);

		pcName = g_array_index(arRow, gchar *, 1);
		pcDescription = g_array_index(arRow, gchar *, 3);
		pcSample = g_array_index(arRow, gchar *, 4);
		pcUrl = g_array_index(arRow, gchar *, 5);

		pcTopic = g_strdup_printf(_("Name : %s\n\nDescription :\n\n%s\n\nSample :\n\n%s\n\nUrl : %s\n"), pcName, pcDescription, pcSample, pcUrl);

		txtBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(pGmlcGuiSrvTabHelp->txvHelpTopic));
		gtk_text_buffer_set_text(txtBuffer, pcTopic, -1);

		gmlc_mysql_query_free_record_content(arRow);
		g_free(pcTopic);
	}

	g_free(pcSql);
	g_object_unref(G_OBJECT(pGmlcMysqlQry));
}
