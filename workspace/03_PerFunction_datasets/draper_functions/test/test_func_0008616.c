matewnck_pager_drag_drop  (GtkWidget        *widget,
		       GdkDragContext   *context,
		       gint              x,
		       gint              y,
		       guint             time)
{
  MatewnckPager *pager = MATEWNCK_PAGER (widget);
  GdkAtom target;

  target = gtk_drag_dest_find_target (widget, context, NULL);

  if (target != GDK_NONE)
    gtk_drag_get_data (widget, context, target, time);
  else
    gtk_drag_finish (context, FALSE, FALSE, time);

  matewnck_pager_clear_drag (pager);
  matewnck_pager_check_prelight (pager, x, y, FALSE);

  return TRUE;
}
