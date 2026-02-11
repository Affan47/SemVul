gtk_plot_canvas_set_pc(GtkPlotCanvas *canvas, GtkPlotPC *pc)
{
  if(canvas->pc)
    gtk_object_unref(GTK_OBJECT(canvas->pc));

  if(!pc){
    canvas->pc = GTK_PLOT_PC(gtk_plot_gdk_new(GTK_WIDGET(canvas)));
    gtk_object_ref(GTK_OBJECT(canvas->pc));
    gtk_object_sink(GTK_OBJECT(canvas->pc));
  } else {
    canvas->pc = pc;
    gtk_object_ref(GTK_OBJECT(pc));
    gtk_object_sink(GTK_OBJECT(pc));
  }

  if(canvas->pc && GTK_IS_PLOT_GDK(canvas->pc)){
       GTK_PLOT_GDK(canvas->pc)->drawable = canvas->pixmap;
  }
  gtk_plot_pc_set_viewport(canvas->pc, canvas->pixmap_width, canvas->pixmap_height);
}
