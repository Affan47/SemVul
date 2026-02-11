terminal_create (TerminalPlugin *term_plugin)
{
	GtkWidget *frame;

	g_return_if_fail(term_plugin != NULL);

	term_plugin->child_pid = 0;


	term_plugin->shell = create_terminal (term_plugin);
	term_plugin->shell_box = create_box (term_plugin->shell);

	term_plugin->term = create_terminal (term_plugin);
	term_plugin->term_box = create_box (term_plugin->term);


	g_signal_connect (G_OBJECT (term_plugin->term), "key-press-event",
					  G_CALLBACK (terminal_keypress_cb), term_plugin);

	frame = gtk_frame_new (NULL);
	gtk_widget_show (frame);
	gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_IN);

	gtk_container_add (GTK_CONTAINER (frame), term_plugin->shell_box);
	gtk_widget_show_all (frame);

	term_plugin->frame = frame;

	init_shell (term_plugin, NULL);
}
