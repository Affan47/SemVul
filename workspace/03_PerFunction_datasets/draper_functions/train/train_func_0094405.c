bonobo_dock_band_drag_end (BonoboDockBand *band, BonoboDockItem *item)
{
  g_return_if_fail (band->doing_drag);

  DEBUG (("entering function"));

  if (band->floating_child != NULL)
    {
      BonoboDockBandChild *f;


      f = (BonoboDockBandChild *) band->floating_child->data;
      g_return_if_fail (f->widget == GTK_WIDGET (item));

      gtk_widget_queue_resize (f->widget);
      band->floating_child = NULL;
    }

  band->doing_drag = FALSE;
  band->new_for_drag = FALSE;
}
