CallBack_PopupMenuPlayer(GtkWidget* widget)  {

	gchar *text;

	guint32 id = atoi( gtk_object_get_data(GTK_OBJECT(widget->parent), "playerid") );
	gchar *action = gtk_object_get_data(GTK_OBJECT(widget), "action");

	if(! strcmp(action, "trade") )  {


		text = g_strdup_printf(".Tn%d\n", id);
		client_send(game->connectid, text, strlen(text));
		g_free(text);
	}

	if(! strcmp(action, "version") )  {


		text = g_strdup_printf("!version %s\n", global->player[ get_player_slot_with_playerid(id) ].name);
		client_send(game->connectid, text, strlen(text));
		g_free(text);
	}

	if(! strcmp(action, "date") )  {


		text = g_strdup_printf("!date %s\n", global->player[ get_player_slot_with_playerid(id) ].name);
		client_send(game->connectid, text, strlen(text));
		g_free(text);
	}

	if(! strcmp(action, "ping") )  {


		text = g_strdup_printf("!ping %s\n", global->player[ get_player_slot_with_playerid(id) ].name);
		client_send(game->connectid, text, strlen(text));
		g_free(text);
	}
}
