egg_tray_icon_manager_filter (GdkXEvent *xevent, GdkEvent *event, gpointer user_data)
{
  EggTrayIcon *icon = user_data;
  XEvent *xev = (XEvent *)xevent;

  if (xev->xany.type == ClientMessage &&
      xev->xclient.message_type == icon->manager_atom &&
      xev->xclient.data.l[1] == icon->selection_atom)
    {
      egg_tray_icon_update_manager_window (icon);
    }
  else if (xev->xany.window == icon->manager_window)
    {
      if (xev->xany.type == DestroyNotify)
	{
	  egg_tray_icon_update_manager_window (icon);
	}
    }

  return GDK_FILTER_CONTINUE;
}
