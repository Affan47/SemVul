traitementExcited (GtkComboBox *combobox, gpointer d)
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
	for(i=0;i<numberOfExcited;i++)
	{
		if(strcmp((gchar*)data,listExcitedView[i])==0) res = listExcitedReal[i];
	}
	if(res) sprintf(selectedExcited,"%s",res);


}
