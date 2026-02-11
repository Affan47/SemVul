receive_scatmat_drag (GtkWidget * src, GdkDragContext * context, int x, int y,
                      const GtkSelectionData * data, unsigned int info,
                      unsigned int event_time, gpointer * udata)
{
  splotd *to = GGOBI_SPLOT (src), *from, *sp;
  displayd *display;
  GList *l;
  gint k, n, sprow, spcol;
  GtkWidget *da;
  GtkTableChild *child;
  GList *ivars = NULL;
  gint nvars, *vars;
  GGobiData *d;
  ggobid *gg;

  display = to->displayptr;
  d = display->d;
  gg = GGobiFromDisplay (display);
  from = GGOBI_SPLOT (gtk_drag_get_source_widget (context));

  if (from->displayptr != display) {
    gg_write_to_statusbar
      ("the source and destination of the scatterplots are not from the same display.\n",
       display->ggobi);
    return;
  }


  if (from->p1dvar != -1 && to->p1dvar != -1) {

    vars = (gint *) g_malloc (d->ncols * sizeof (gint));
    nvars =
      GGOBI_EXTENDED_DISPLAY_GET_CLASS (display)->plotted_vars_get (display,
                                                                    vars, d,
                                                                    gg);


    for (n = 0; n < nvars; n++)
      ivars = g_list_append (ivars, GINT_TO_POINTER (vars[n]));

    k = g_list_index (ivars, GINT_TO_POINTER (to->p1dvar));

    ivars = g_list_remove (ivars, GINT_TO_POINTER (from->p1dvar));

    ivars = g_list_insert (ivars, GINT_TO_POINTER (from->p1dvar), k);


    for (l = (GTK_TABLE (display->table))->children; l; l = l->next) {
      child = (GtkTableChild *) l->data;
      da = child->widget;
      sp = (splotd *) g_object_get_data (G_OBJECT (da), "splotd");
      sprow = child->top_attach;
      spcol = child->left_attach;
      if (sprow == spcol) {
        sp->p1dvar = GPOINTER_TO_INT (g_list_nth_data (ivars, sprow));
      }
      else {
        sp->p1dvar = -1;
        sp->xyvars.x = GPOINTER_TO_INT (g_list_nth_data (ivars, spcol));
        sp->xyvars.y = GPOINTER_TO_INT (g_list_nth_data (ivars, sprow));
      }
    }

    display_tailpipe (display, FULL, display->ggobi);
    varpanel_refresh (display, display->ggobi);

    g_free (vars);
  }
}
