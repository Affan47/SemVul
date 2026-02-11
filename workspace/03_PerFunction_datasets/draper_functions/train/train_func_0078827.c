set_axis(GtkWidget* fp,gpointer data)
{
	GtkWidget** entrys = (GtkWidget**)data;
	gdouble  *vFirst = g_object_get_data(G_OBJECT (fp), "FirstColor");
	gdouble  *vSecond = g_object_get_data(G_OBJECT (fp), "SecondColor");
	gdouble  *vThird = g_object_get_data(G_OBJECT (fp), "ThirdColor");
	gboolean  *negative = g_object_get_data(G_OBJECT (fp), "Negative");
	G_CONST_RETURN gchar* tentry;
	gint i;

	tentry = gtk_entry_get_text(GTK_ENTRY(entrys[0]));
	axis.scal = atof(tentry);
	if(axis.scal<1e-6) axis.scal = 1.0;
	for(i=1;i<4;i++)
	{
		tentry = gtk_entry_get_text(GTK_ENTRY(entrys[i]));
		axis.origin[i-1] = atof(tentry)*ANG_TO_BOHR;
	}

	tentry = gtk_entry_get_text(GTK_ENTRY(entrys[4]));
	axis.radius = atof(tentry)*ANG_TO_BOHR;

	if(axis.radius<1e-6) axis.radius = 0.1;

	for(i=0;i<3;i++)
	{
		 axis.firstColor[i] = vFirst[i];
		 axis.secondColor[i] = vSecond[i];
		 axis.thirdColor[i] = vThird[i];
	}
	axis.negative = *negative;
	rafresh_window_orb();
}
