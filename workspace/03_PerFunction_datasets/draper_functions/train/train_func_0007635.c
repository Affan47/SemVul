gtk_cmoption_menu_select_first_sensitive (GtkCMOptionMenu *option_menu)
{
  if (option_menu->menu)
    {
      GList *children = gtk_container_get_children (GTK_CONTAINER (GTK_MENU_SHELL (option_menu->menu)));
      gint index = 0;

      while (children)
	{
	  if (gtk_widget_get_sensitive (children->data))
	    {
	      gtk_cmoption_menu_set_history (option_menu, index);
	      return;
	    }

	  children = children->next;
	  index++;
	}

	g_list_free (children);
    }
}
