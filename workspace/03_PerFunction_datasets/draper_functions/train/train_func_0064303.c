reset_parameters(GtkWidget *win, gpointer data)
{
	gdouble velo   = atof(gtk_entry_get_text(GTK_ENTRY(EntryVelocity)));
	gint nSurf     = atoi(gtk_entry_get_text(GTK_ENTRY(EntryNIsoSurface)));
	gdouble minIso = atof(gtk_entry_get_text(GTK_ENTRY(EntryMinIsoValue)));
	gdouble maxIso = atof(gtk_entry_get_text(GTK_ENTRY(EntryMaxIsoValue)));

	gchar t[BSIZE];

	if(velo<0)
	{
		velo = -velo;
		sprintf(t,"%lf",velo);
		gtk_entry_set_text(GTK_ENTRY(EntryVelocity),t);
	}
	velocity = velo;

	if(nSurf<=1)
	{
		nSurf = 10;
		sprintf(t,"%d",nSurf);
		gtk_entry_set_text(GTK_ENTRY(EntryNIsoSurface),t);
	}
	if(nSurf<0)
	{
		nSurf = -nSurf;
		sprintf(t,"%d",nSurf);
		gtk_entry_set_text(GTK_ENTRY(EntryNIsoSurface),t);
	}
	nIsoSurface = nSurf;
	if(minIso<0)
	{
		minIso = -minIso;
		if(minIso==0) minIso = 0.01;
		sprintf(t,"%lf",minIso);
		gtk_entry_set_text(GTK_ENTRY(EntryMinIsoValue),t);
	}
	minIsoValue = minIso;
	if(maxIso<0)
	{
		maxIso = -maxIso;
		if(maxIso==0) maxIso = 0.05;
		sprintf(t,"%lf",maxIso);
		gtk_entry_set_text(GTK_ENTRY(EntryMaxIsoValue),t);
	}
	maxIsoValue = maxIso;
	if(data) setColorMap(-maxIsoValue, maxIsoValue);

	if(!play)
		stop_animation(NULL,NULL);

}
