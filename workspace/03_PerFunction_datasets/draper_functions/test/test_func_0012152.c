wmsortfunc(GtkTreeModel *model, GtkTreeIter  *item1, GtkTreeIter  *item2, gpointer      user_data) {
	gchar *name1,*name2;
	gint ret;

	gtk_tree_model_get(model,item1,col_name,&name1,-1);
	gtk_tree_model_get(model,item2,col_name,&name2,-1);
	if( name1 == NULL )
		if( name2 == NULL )
			ret = 0;
		else
			ret =  -1;
	else
		if( name1 == NULL )
			ret = 1;
		else
			ret = g_utf8_collate(name1,name2);
	g_free(name1);
	g_free(name2);
	return ret;
}
