trash_applet_key_press (GtkWidget   *widget,
                        GdkEventKey *event)
{
  TrashApplet *applet = TRASH_APPLET (widget);

  switch (event->keyval)
    {
     case GDK_KEY_KP_Enter:
     case GDK_KEY_ISO_Enter:
     case GDK_KEY_3270_Enter:
     case GDK_KEY_Return:
     case GDK_KEY_space:
     case GDK_KEY_KP_Space:
      trash_applet_open_folder (NULL, applet);
      return TRUE;

     default:
      break;
    }

  if (GTK_WIDGET_CLASS (trash_applet_parent_class)->key_press_event)
    return GTK_WIDGET_CLASS (trash_applet_parent_class)
      ->key_press_event (widget, event);
  else
    return FALSE;
}
