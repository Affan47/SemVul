barchartDestroy (GtkObject * obj)
{
  if (obj && GGOBI_BARCHART_SPLOT (obj)->bar) {
    GtkObjectClass *klass;
    barchartSPlotd *sp;

    sp = GGOBI_BARCHART_SPLOT (obj);


    klass = g_type_class_peek_parent (GGOBI_EXTENDED_SPLOT_GET_CLASS (sp));

    barchart_free_structure (sp);
    vectori_free (&sp->bar->index_to_rank);
    g_free ((gpointer) sp->bar);
    sp->bar = NULL;

    klass->destroy (GTK_OBJECT (sp));
  }
}
