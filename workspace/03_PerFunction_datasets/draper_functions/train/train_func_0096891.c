gtk_plot_real_set_pc(GtkPlot *plot, GtkPlotPC *pc)
{
  if(plot->pc)
    gtk_object_unref(GTK_OBJECT(plot->pc));

  if(!pc){
    plot->pc = GTK_PLOT_PC(gtk_plot_gdk_new(GTK_WIDGET(plot)));
    gtk_object_ref(GTK_OBJECT(plot->pc));
    gtk_object_sink(GTK_OBJECT(plot->pc));
  } else {
    plot->pc = pc;
    gtk_object_ref(GTK_OBJECT(plot->pc));
    gtk_object_sink(GTK_OBJECT(plot->pc));
  }
}
