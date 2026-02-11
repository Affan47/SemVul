gc_im_init(GtkWidget *window)
{
  GcomprisProperties	*properties = gc_prop_get ();


  properties->context = gtk_im_multicontext_new ();

  if(gc_profile_get_current())
    {
      GHashTable *init_im =  g_hash_table_new_full (g_str_hash, g_str_equal, g_free, g_free);
      init_im = gc_db_conf_with_table_get (gc_profile_get_current()->profile_id,
					      -1,
					      init_im );

      properties->default_context = g_hash_table_lookup ( init_im, "default_im");

      if (properties->default_context)
	g_setenv ("GTK_IM_MODULE",
		  properties->default_context,
		  TRUE);
    }

  gtk_im_context_set_client_window (properties->context,
                                    window->window);

  g_signal_connect (G_OBJECT (properties->context), "commit",
		    G_CALLBACK(im_context_commit_callback), NULL);

  g_signal_connect (G_OBJECT (properties->context), "preedit-changed",
		    G_CALLBACK(im_context_preedit_callback), NULL);

  g_signal_connect (GTK_WIDGET (window), "focus-in-event",
		    G_CALLBACK(window_focus_callback), NULL);

  g_signal_connect (GTK_WIDGET (window), "focus-out-event",
		    G_CALLBACK(window_focus_callback), NULL);

}
