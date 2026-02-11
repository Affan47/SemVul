add_record_dialog_apply (GtkWidget * w, displayd * display)
{
  gint j;
  cpaneld *cpanel = &display->cpanel;
  GGobiData *d = display->d;
  GGobiData *e = display->e;
  ggobid *gg = d->gg;
  GtkWidget *dialog = gtk_widget_get_toplevel (w);
  GtkWidget *label_entry, *id_entry;
  gchar *label = NULL, *id = NULL;
  gchar **vals = NULL;
  GGobiData *dtarget;

  dtarget = (cpanel->ee_mode == ADDING_EDGES) ? e : d;
  if (dtarget->ncols) {
    GList *list;
    GtkTableChild *child;
    GtkWidget *entry;
    gchar *lbl;
    GtkWidget *table = widget_find_by_name (GTK_DIALOG (dialog)->vbox,
                                            "EE:tablev");

    vals = (gchar **) g_malloc (d->ncols * sizeof (gchar *));

    for (list = GTK_TABLE (table)->children; list; list = list->next) {
      child = (GtkTableChild *) list->data;
      if (child->left_attach == 1) {
        entry = child->widget;
        lbl = gtk_editable_get_chars (GTK_EDITABLE (entry), 0, -1);
        vals[child->top_attach] = g_strdup (lbl);
      }
    }
  }


  if ((label_entry = widget_find_by_name (GTK_DIALOG (dialog)->vbox,
                                          "EE:rowlabel"))) {
    label = gtk_editable_get_chars (GTK_EDITABLE (label_entry), 0, -1);
  }

  if ((id_entry = widget_find_by_name (GTK_DIALOG (dialog)->vbox,
                                       "EE:recordid"))) {
    id = gtk_editable_get_chars (GTK_EDITABLE (id_entry), 0, -1);
  }

  if (cpanel->ee_mode == ADDING_EDGES) {

    record_add (cpanel->ee_mode, gg->edgeedit.a, d->nearest_point,
                label, id, vals, d, e, gg);

  }
  else if (cpanel->ee_mode == ADDING_POINTS) {
    record_add (cpanel->ee_mode, -1, -1, label, id, vals, d, e, gg);
  }

  if (vals) {
    for (j = 0; j < d->ncols; j++)
      g_free (vals[j]);
    g_free (vals);
  }

  gg->edgeedit.a = -1;
  gtk_widget_destroy (dialog);
  edgeedit_event_handlers_toggle (gg->current_splot, true);
}
