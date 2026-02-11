getPointsFromList(GtkWidget* list, gdouble** pX, gdouble** pY, gint* pn)
{
        GtkTreeIter iter;
	GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));
	gchar* dataMass = NULL;
	gchar* dataAbund = NULL;
	gint i;
	gint n = 0;
	gchar* path_string = NULL;
	gdouble* X = NULL;
	gdouble* Y = NULL;
	GtkWidget* xyplot = g_object_get_data(G_OBJECT(list),"XYPlot");
	GtkWidget* entryCharge = g_object_get_data(G_OBJECT(list),"EntryCharge");
	gdouble charge = 1.0;

	if(!pX || !pY) return NULL;
	*pX = NULL;
	*pY = NULL;
	if(!xyplot) return NULL;
	if(!GTK_IS_WIDGET(xyplot)) return NULL;
	if(entryCharge)
	{
		G_CONST_RETURN gchar* tentry;
		tentry = gtk_entry_get_text(GTK_ENTRY(entryCharge));
		charge = atof(tentry);
		if(charge<1e-12) charge = 1.0;
	}
	do{

	  	path_string = g_strdup_printf("%d",n);
		if(!gtk_tree_model_get_iter_from_string (model, &iter, path_string))break;
		n++;
	}while(TRUE);

	if(n<1) return NULL;
	X = g_malloc(n*sizeof(gdouble));
	Y = g_malloc(n*sizeof(gdouble));
	for(i=0;i<n;i++) X[i] = Y[i] = 0;
	i = 0;
	do{

	  	path_string = g_strdup_printf("%d",i);
		if(!gtk_tree_model_get_iter_from_string (model, &iter, path_string))break;
		dataMass = NULL;
		dataAbund = NULL;
		gtk_tree_model_get (model, &iter, 0, &dataMass, 4, &dataAbund, -1);
		if(dataMass && dataAbund)
		{
			X[i] = atof(dataMass)/charge;
			Y[i] = atof(dataAbund);
		}
		i++;
	}while(i<n);
	*pX = X;
	*pY = Y;
	*pn = n;
	return xyplot;

}
