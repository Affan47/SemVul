parcoords_reset_arrangement (displayd *display, gint arrangement, ggobid *gg) {
  GList *l;
  GtkWidget *frame, *w;
  splotd *sp;
  gint x, y, width, height, depth;
  gint wframe, hframe;
  GdkWindow *window;

  if (display->cpanel.parcoords_arrangement == arrangement)
    return;

  for (l=display->splots; l; l=l->next) {
    w = ((splotd *) l->data)->da;
    gtk_widget_ref (w);
    gtk_container_remove (GTK_CONTAINER (gg->parcoords.arrangement_box), w);
  }

  frame = gg->parcoords.arrangement_box->parent;


  window = gtk_widget_get_parent_window (frame);
  gdk_window_get_geometry(window, &x, &y, &width, &height, &depth);
  wframe = (arrangement == ARRANGE_ROW) ? MAX(width,height) :
    MIN(width,height);
  hframe = (arrangement == ARRANGE_ROW) ? MIN(width,height) :
    MAX(width,height);
  gdk_window_resize(window, wframe, hframe);

  gtk_widget_destroy (gg->parcoords.arrangement_box);

  if (arrangement == ARRANGE_ROW)
    gg->parcoords.arrangement_box = gtk_hbox_new (true, 0);
  else
    gg->parcoords.arrangement_box = gtk_vbox_new (true, 0);
  gtk_container_add (GTK_CONTAINER (frame), gg->parcoords.arrangement_box);

  display->p1d_orientation = (arrangement == ARRANGE_ROW) ? VERTICAL :
                                                            HORIZONTAL;

  for (l=display->splots; l; l=l->next) {
    sp = (splotd *) l->data;
    gtk_box_pack_start (GTK_BOX (gg->parcoords.arrangement_box),
                        sp->da, true, true, 0);
    gtk_widget_unref (sp->da);
  }


  display_set_position (GGOBI_WINDOW_DISPLAY(display), gg);

  gtk_widget_show_all (gg->parcoords.arrangement_box);

  display_tailpipe (display, FULL, gg);

  varpanel_refresh (display, gg);
}
