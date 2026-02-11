deleteBasisDlg(GtkWidget *win,gpointer d)
{

	gchar *format ="Do you want to really delete \"%s.%s\" basis for \"%s\" atom ?" ;
	gchar *t =NULL;
  	GtkTreeIter node;
   	DataMolcasTree* data = NULL;
	gint atomNumber;
	gint basisNumber;
	GtkWidget* w = NULL;
	GtkTreeModel *model = gtk_tree_view_get_model(GTK_TREE_VIEW(treeView));

	if(!gtk_tree_model_get_iter_from_string (model, &node, selectedRow)) return;
	gtk_tree_model_get (model, &node, LIST_DATA, &data, -1);

	if(!data) return;

	atomNumber = data->atomNumber;
	basisNumber = data->basisNumber;

	if(atomNumber<0)
		return;
	if(basisNumber<0)
		return;

	t =g_strdup_printf(format,
			molcasBasis.atoms[atomNumber].basis[basisNumber].basisName,
			molcasBasis.atoms[atomNumber].basis[basisNumber].author,
			molcasBasis.atoms[atomNumber].symbol
			);

	w = Continue_YesNo(deleteOneBasis, NULL,t);
	gtk_window_set_modal(GTK_WINDOW(w),TRUE);
  	gtk_window_set_transient_for(GTK_WINDOW(w),GTK_WINDOW(SetWinDlg));
}
