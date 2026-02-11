gtk_plot_canvas_child_move(GtkPlotCanvas *canvas,
                           GtkPlotCanvasChild *child,
			   gdouble x1, gdouble y1)
{
  child->rx2 += (x1 - child->rx1);
  child->ry2 += (y1 - child->ry1);
  child->rx1 = x1;
  child->ry1 = y1;

  if(GTK_PLOT_CANVAS_CHILD_CLASS(GTK_OBJECT_GET_CLASS(GTK_OBJECT(child)))->move)
    GTK_PLOT_CANVAS_CHILD_CLASS(GTK_OBJECT_GET_CLASS(GTK_OBJECT(child)))->move(canvas, child, x1, y1);
  GTK_PLOT_CANVAS_CHILD_CLASS(GTK_OBJECT_GET_CLASS(GTK_OBJECT(child)))->size_allocate(canvas, child);
  gtk_plot_canvas_paint(canvas);
  gtk_plot_canvas_refresh(canvas);
  gtk_signal_emit (GTK_OBJECT(canvas), canvas_signals[CHANGED]);
}
