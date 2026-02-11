brasero_player_bacon_init (BraseroPlayerBacon *obj)
{
	gtk_widget_set_double_buffered (GTK_WIDGET (obj), FALSE);

	obj->priv = g_new0 (BraseroPlayerBaconPrivate, 1);
	brasero_player_bacon_setup_pipe (obj);
}
