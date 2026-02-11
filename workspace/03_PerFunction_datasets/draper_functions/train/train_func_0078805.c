gtk_plot_dt_inside_triangle(GtkPlotDT *data, GtkPlotDTtriangle *t,
			    GtkPlotDTnode *n)
{
  gdouble A,B;
  GtkPlotDTnode *a,*b,*c;
  if (!t || !n) return 1e99;


  if ((n->x < t->min.x) || (n->x > t->max.x) ||
      (n->y < t->min.y) || (n->y > t->max.y)) return 1e99;

  a= t->na;
  b= t->nb;
  c= t->nc;

  A= t->area;
  if (A==0.0) A= t->area= gtk_plot_dt_area_triangle(a,b,c);
  B= gtk_plot_dt_area_triangle(n,a,b)+
     gtk_plot_dt_area_triangle(n,b,c)+
     gtk_plot_dt_area_triangle(n,c,a);


  return B/A;
}
