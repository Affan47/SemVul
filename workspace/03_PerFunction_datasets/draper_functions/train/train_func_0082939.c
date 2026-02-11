traitementCorrMethod (GtkComboBox *combobox, gpointer d)
{
	GtkTreeIter iter;
	gchar* data = NULL;
	gchar* res = NULL;
	gint i;

	if (gtk_combo_box_get_active_iter (combobox, &iter))
	{
		GtkTreeModel* model = gtk_combo_box_get_model(combobox);
		gtk_tree_model_get (model, &iter, 0, &data, -1);
	}
	else return;
	for(i=0;i<numberOfCorrMethods;i++)
	{
		if(strcmp((gchar*)data,listCorrMethodsView[i])==0) res = listCorrMethodsReal[i];
	}
	if(res) sprintf(selectedCorrMethod,"%s",res);
	else  sprintf(selectedSCF,"NONE");
}
