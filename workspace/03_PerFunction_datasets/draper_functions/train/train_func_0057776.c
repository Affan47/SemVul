glade_gtk_notebook_set_n_pages (GObject * object, const GValue * value)
{
  GladeWidget *widget;
  GtkNotebook *notebook;
  GtkWidget *child_widget;
  gint new_size, i;
  gint old_size;

  notebook = GTK_NOTEBOOK (object);
  g_return_if_fail (GTK_IS_NOTEBOOK (notebook));

  widget = glade_widget_get_from_gobject (GTK_WIDGET (notebook));
  g_return_if_fail (widget != NULL);

  new_size = g_value_get_int (value);
  old_size = gtk_notebook_get_n_pages (GTK_NOTEBOOK (notebook));


  if (glade_widget_superuser () == FALSE)
    {
      for (i = gtk_notebook_get_n_pages (notebook); i < new_size; i++)
        {
          gint position = glade_gtk_notebook_get_first_blank_page (notebook);
          GtkWidget *placeholder = glade_placeholder_new ();
          GladeWidget *gtab;

          gtk_notebook_insert_page (notebook, placeholder, NULL, position);


          if (old_size == 0 && new_size > 1)
            {
              gtab = glade_gtk_notebook_generate_tab (widget, position + 1);


              glade_widget_add_child (widget, gtab, FALSE);
            }
          else
            {
              GtkWidget *tab_placeholder = glade_placeholder_new ();

              g_object_set_data (G_OBJECT (tab_placeholder),
                                 "special-child-type", "tab");

              gtk_notebook_set_tab_label (GTK_NOTEBOOK (notebook), placeholder,
                                          tab_placeholder);
            }
        }
    }


  while (old_size > new_size)
    {


      child_widget = gtk_notebook_get_nth_page (notebook, old_size - 1);


      if (glade_widget_get_from_gobject (child_widget))
        g_critical ("Bug in notebook_set_n_pages()");

      gtk_notebook_remove_page (notebook, old_size - 1);

      old_size--;
    }
}
