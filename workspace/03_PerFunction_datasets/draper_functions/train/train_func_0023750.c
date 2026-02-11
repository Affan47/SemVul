gtk_plot_dt_triangle_subsample(GtkPlotDT *data,
			       GtkPlotDTtriangle *t1,
			       GtkPlotDTtriangle *t2)
{
  gint i,tmp;
  GtkPlotDTnode *n= NULL;
  gint a= 0,b= 0,c= 0,d= 0, found= 0;
  gint u[3], v[3];

  u[0] = t1->a;
  u[1] = t1->b;
  u[2] = t1->c;
  v[0] = t2->a;
  v[1] = t2->b;
  v[2] = t2->c;

  for (i=0; i<4; i++) {
    if (u[0]==v[0] && u[1]==v[2]) {
      a= u[0]; b=v[1]; c=u[1]; d= u[2]; found++; break;
    }
    if (u[1]==v[1] && u[2]==v[0]) {
      a= u[0]; b=u[1]; c=v[2]; d= u[2]; found++; break;
    }
    if (u[0]==v[0] && u[2]==v[1]) {
      a= u[0]; b=u[1]; c=u[2]; d= v[2]; found++; break;
    }

    tmp= v[0]; v[0]= v[1]; v[1]= v[2]; v[2]= tmp;
  }
  if (found) {
    n= g_new(GtkPlotDTnode,1);
    gtk_plot_dt_create_center_node_4(n,
				     gtk_plot_dt_get_node(data,a),
				     gtk_plot_dt_get_node(data,b),
				     gtk_plot_dt_get_node(data,c),
				     gtk_plot_dt_get_node(data,d));
  }
  return n;
}
