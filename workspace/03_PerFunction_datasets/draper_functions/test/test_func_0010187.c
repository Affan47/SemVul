scatmat_add_plot (gint xvar, gint yvar, gint col, gint row,
                  displayd * display, ggobid * gg)
{
  splotd *sp_new;

  sp_new = g_object_new (GGOBI_TYPE_SCATMAT_SPLOT, NULL);
  splot_init (sp_new, display, gg);

  sp_new->xyvars.x = xvar;
  sp_new->xyvars.y = yvar;
  sp_new->p1dvar = (sp_new->xyvars.x == sp_new->xyvars.y) ? xvar : -1;

  gtk_table_attach (GTK_TABLE (display->table),
                    sp_new->da, col, col + 1, row, row + 1,
                    (GtkAttachOptions) (GTK_SHRINK | GTK_FILL | GTK_EXPAND),
                    (GtkAttachOptions) (GTK_SHRINK | GTK_FILL | GTK_EXPAND),
                    1, 1);
  gtk_widget_show (sp_new->da);


  display->splots = g_list_append (display->splots, (gpointer) sp_new);

  return sp_new;
}
