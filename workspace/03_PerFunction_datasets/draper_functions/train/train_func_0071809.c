gtk_cmclist_set_vadjustment (GtkCMCList      *clist,
			   GtkAdjustment *adjustment)
{
  GtkAdjustment *old_adjustment;

  cm_return_if_fail (GTK_IS_CMCLIST (clist));
  if (adjustment)
    cm_return_if_fail (GTK_IS_ADJUSTMENT (adjustment));

  if (clist->vadjustment == adjustment)
    return;

  old_adjustment = clist->vadjustment;

  if (clist->vadjustment)
    {
      g_signal_handlers_disconnect_matched(G_OBJECT (clist->vadjustment), G_SIGNAL_MATCH_DATA,
		      	0, 0, 0, 0, clist);
      g_object_unref (G_OBJECT (clist->vadjustment));
    }

  clist->vadjustment = adjustment;

  if (clist->vadjustment)
    {
#if GLIB_CHECK_VERSION(2,10,0)
      g_object_ref_sink (clist->vadjustment);
#else
      gtk_object_ref (G_OBJECT (clist->vadjustment));
      gtk_object_sink (G_OBJECT (clist->vadjustment));
#endif

      g_signal_connect (G_OBJECT (clist->vadjustment), "value_changed",
			  G_CALLBACK(vadjustment_value_changed),
			  (gpointer) clist);
    }

  if (!clist->vadjustment || !old_adjustment)
    gtk_widget_queue_resize (GTK_WIDGET (clist));
}
