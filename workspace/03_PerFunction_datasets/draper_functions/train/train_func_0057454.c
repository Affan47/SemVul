onPageChanged(GtkNotebook *book, GtkWidget *child,
			  gint num, gpointer data)
{
  VisuUiDockWindow *window;
  int numOld;
#if GTK_MAJOR_VERSION == 2
  child = gtk_notebook_get_nth_page(book, num);
#endif

  window = (VisuUiDockWindow*)data;
  g_return_if_fail(window);
  g_return_if_fail(VISU_UI_IS_PANEL(child));

  DBG_fprintf(stderr, "Gtk VisuUiPanel: caught 'page-switch' signal, jump to %d.\n", num);

  if (!local_class->showHeader)
    {
      numOld = gtk_combo_box_get_active(GTK_COMBO_BOX(window->combo));
      if ((gint)num != numOld)
	{


	  changeHeaderVisibility
	    (VISU_UI_PANEL(gtk_notebook_get_nth_page(book, numOld)), FALSE);
	  changeHeaderVisibility
	    (VISU_UI_PANEL(gtk_notebook_get_nth_page(book, num)), TRUE);
	}
    }


  g_signal_handler_block(G_OBJECT(window->combo), window->comboChanged);
  gtk_combo_box_set_active(GTK_COMBO_BOX(window->combo), num);
  g_signal_handler_unblock(G_OBJECT(window->combo), window->comboChanged);

  g_idle_add(emitPageEnter, child);
}
