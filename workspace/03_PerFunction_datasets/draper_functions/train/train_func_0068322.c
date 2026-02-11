link_item_event (GnomeCanvasItem * item, GdkEvent * event,
		 canvas_link_t * canvas_link)
{
  gchar *str;
  const link_t *link=NULL;

  switch (event->type)
    {
    case GDK_2BUTTON_PRESS:
      if (canvas_link)
        link_info_window_create( &canvas_link->canvas_link_id );
      break;

    case GDK_ENTER_NOTIFY:
      if (canvas_link)
        link = links_catalog_find(&canvas_link->canvas_link_id);
      if (link && link->main_prot[pref.stack_level])
	str = g_strdup_printf (_("Link main protocol: %s"),
			   link->main_prot[pref.stack_level]);
      else
	str = g_strdup_printf (_("Link main protocol unknown"));
      gtk_statusbar_push(appdata.statusbar, 1, str);
      g_free (str);
      break;
    case GDK_LEAVE_NOTIFY:
      gtk_statusbar_pop(appdata.statusbar, 1);
      break;
    default:
      break;
    }

  return FALSE;
}
