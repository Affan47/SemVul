onComboChanged(GtkComboBox *combo, gpointer data)
{
  int index, numOld;
  VisuUiDockWindow *window;
  GtkNotebook *book;

  window = (VisuUiDockWindow*)data;
  g_return_if_fail(window);

  index = gtk_combo_box_get_active(combo);


  if (!local_class->showHeader)
    {
      book = GTK_NOTEBOOK(window->notebook);
      numOld = gtk_notebook_get_current_page(book);
      changeHeaderVisibility
	(VISU_UI_PANEL(gtk_notebook_get_nth_page(book, numOld)), FALSE);
      changeHeaderVisibility
	(VISU_UI_PANEL(gtk_notebook_get_nth_page(book, index)), TRUE);
    }


  gtk_notebook_set_current_page(GTK_NOTEBOOK(window->notebook), index);
}
